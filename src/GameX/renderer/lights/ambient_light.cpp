#include "GameX/renderer/lights/ambient_light.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"
#include "GameX/shaders/shaders.h"

namespace GameX::Graphics {
AmbientLight::AmbientLight(struct Scene *scene,
                           const AmbientLight::AmbientLightData &settings)
    : Light(scene) {
  buffer_ =
      std::make_unique<grassland::vulkan::DynamicBuffer<AmbientLightData>>(
          scene_->Renderer()->App()->VkCore(), 1,
          VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);

  buffer_->At(0) = settings;

  scene_->Renderer()->RegisterSyncObject(buffer_.get());

  descriptor_sets_.resize(
      scene_->Renderer()->App()->VkCore()->MaxFramesInFlight());

  for (size_t i = 0; i < descriptor_sets_.size(); ++i) {
    descriptor_sets_[i] = std::make_unique<grassland::vulkan::DescriptorSet>(
        scene_->Renderer()->App()->VkCore(), scene_->DescriptorPool(),
        AmbientLightDescriptorSetLayout(scene_->Renderer()));

    VkDescriptorBufferInfo buffer_info = {};
    buffer_info.buffer = buffer_->GetBuffer(i)->Handle();
    buffer_info.offset = 0;
    buffer_info.range = sizeof(AmbientLightData);

    VkWriteDescriptorSet write_descriptor_set = {};
    write_descriptor_set.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_descriptor_set.dstSet = descriptor_sets_[i]->Handle();
    write_descriptor_set.dstBinding = 0;
    write_descriptor_set.dstArrayElement = 0;
    write_descriptor_set.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    write_descriptor_set.descriptorCount = 1;
    write_descriptor_set.pBufferInfo = &buffer_info;

    vkUpdateDescriptorSets(
        scene_->Renderer()->App()->VkCore()->Device()->Handle(), 1,
        &write_descriptor_set, 0, nullptr);
  }
}

AmbientLight::AmbientLight(PScene scene, glm::vec3 color, float intensity)
    : AmbientLight(scene, {color, intensity}) {
}

AmbientLight::~AmbientLight() {
  scene_->Renderer()->UnregisterSyncObject(buffer_.get());
}

grassland::vulkan::Pipeline *AmbientLight::LightingPipeline() {
  return AmbientLightPipeline(scene_->Renderer());
}

void AmbientLight::Lighting(VkCommandBuffer cmd_buffer, int frame_index) {
  VkDescriptorSet descriptor_sets[] = {descriptor_sets_[frame_index]->Handle()};

  vkCmdBindDescriptorSets(
      cmd_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
      LightingPipeline()->Settings().pipeline_layout->Handle(), 1, 1,
      descriptor_sets, 0, nullptr);

  vkCmdDraw(cmd_buffer, 6, 1, 0, 0);
}

void AmbientLight::SetLight(glm::vec3 color, float intensity) {
  buffer_->At(0) = {color, intensity};
}

grassland::vulkan::DescriptorSetLayout *AmbientLightDescriptorSetLayout(
    struct Renderer *renderer) {
  static std::map<Renderer *, grassland::vulkan::DescriptorSetLayout *>
      ambient_light_descriptor_set_layouts;
  if (!ambient_light_descriptor_set_layouts.count(renderer)) {
    auto &ambient_light_descriptor_set_layout =
        ambient_light_descriptor_set_layouts[renderer];
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    bindings.resize(1);
    bindings[0].binding = 0;
    bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    bindings[0].descriptorCount = 1;
    bindings[0].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    bindings[0].pImmutableSamplers = nullptr;

    ambient_light_descriptor_set_layout =
        new grassland::vulkan::DescriptorSetLayout(renderer->App()->VkCore(),
                                                   bindings);
    renderer->AddReleaseCallback([ambient_light_descriptor_set_layout]() {
      delete ambient_light_descriptor_set_layout;
    });
    return ambient_light_descriptor_set_layout;
  }
  return ambient_light_descriptor_set_layouts.at(renderer);
}

grassland::vulkan::Pipeline *AmbientLightPipeline(struct Renderer *renderer) {
  static std::map<Renderer *, PipelineAssets> ambient_light_pipelines;
  auto &pipeline = ambient_light_pipelines[renderer];
  if (!pipeline.pipeline) {
    pipeline.vertex_shader = new grassland::vulkan::ShaderModule(
        renderer->App()->VkCore(),
        BuiltInShaderSpv("fullscreen_lighting_pass.vert"));
    pipeline.fragment_shader = new grassland::vulkan::ShaderModule(
        renderer->App()->VkCore(), BuiltInShaderSpv("ambient_light.frag"));

    pipeline.pipeline_layout = new grassland::vulkan::PipelineLayout(
        renderer->App()->VkCore(),
        std::vector<grassland::vulkan::DescriptorSetLayout *>{
            renderer->RenderPipeline()->LightingPassDescriptorSetLayout(),
            AmbientLightDescriptorSetLayout(renderer)});

    grassland::vulkan::PipelineSettings ambient_light_pipeline_settings(
        renderer->RenderPipeline()->RenderPass(), pipeline.pipeline_layout, 1);
    ambient_light_pipeline_settings.AddShaderStage(pipeline.vertex_shader,
                                                   VK_SHADER_STAGE_VERTEX_BIT);
    ambient_light_pipeline_settings.AddShaderStage(
        pipeline.fragment_shader, VK_SHADER_STAGE_FRAGMENT_BIT);
    ambient_light_pipeline_settings.SetPrimitiveTopology(
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

    ambient_light_pipeline_settings.SetMultiSampleState(VK_SAMPLE_COUNT_1_BIT);

    ambient_light_pipeline_settings.SetCullMode(VK_CULL_MODE_NONE);

    ambient_light_pipeline_settings.SetBlendState(
        0, VkPipelineColorBlendAttachmentState{
               VK_TRUE,
               VK_BLEND_FACTOR_ONE,
               VK_BLEND_FACTOR_ONE,
               VK_BLEND_OP_ADD,
               VK_BLEND_FACTOR_ONE,
               VK_BLEND_FACTOR_ZERO,
               VK_BLEND_OP_ADD,
               VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                   VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
           });

    pipeline.pipeline = new grassland::vulkan::Pipeline(
        renderer->App()->VkCore(), ambient_light_pipeline_settings);
    renderer->AddReleaseCallback([pipeline]() {
      delete pipeline.pipeline;
      delete pipeline.pipeline_layout;
      delete pipeline.vertex_shader;
      delete pipeline.fragment_shader;
    });
  }
  return pipeline.pipeline;
}
}  // namespace GameX::Graphics
