#include "GameX/renderer/lights/directional_light.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"
#include "GameX/shaders/shaders.h"

namespace GameX::Graphics {
DirectionalLight::DirectionalLight(Scene *scene,
                                   const DirectionalLightData &settings)
    : Light(scene) {
  buffer_ =
      std::make_unique<grassland::vulkan::DynamicBuffer<DirectionalLightData>>(
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
    buffer_info.range = sizeof(DirectionalLightData);

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

DirectionalLight::~DirectionalLight() {
  scene_->Renderer()->UnregisterSyncObject(buffer_.get());
}

grassland::vulkan::Pipeline *DirectionalLight::LightingPipeline() {
  return DirectionalLightPipeline(scene_->Renderer());
}

void DirectionalLight::Lighting(VkCommandBuffer cmd_buffer, int frame_index) {
  VkDescriptorSet descriptor_sets[] = {descriptor_sets_[frame_index]->Handle()};

  vkCmdBindDescriptorSets(
      cmd_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
      LightingPipeline()->Settings().pipeline_layout->Handle(), 1, 1,
      descriptor_sets, 0, nullptr);

  vkCmdDraw(cmd_buffer, 6, 1, 0, 0);
}

DirectionalLight::DirectionalLight(struct Scene *scene,
                                   glm::vec3 color,
                                   glm::vec3 direction,
                                   float intensity)
    : DirectionalLight(
          scene,
          DirectionalLightData{color, intensity, glm::normalize(direction)}) {
}

grassland::vulkan::DescriptorSetLayout *DirectionalLightDescriptorSetLayout(
    struct Renderer *renderer) {
  static std::map<Renderer *, grassland::vulkan::DescriptorSetLayout *>
      directional_light_descriptor_set_layouts;
  auto &directional_light_descriptor_set_layout =
      directional_light_descriptor_set_layouts[renderer];
  if (!directional_light_descriptor_set_layout) {
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    bindings.resize(1);
    bindings[0].binding = 0;
    bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    bindings[0].descriptorCount = 1;
    bindings[0].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    bindings[0].pImmutableSamplers = nullptr;

    directional_light_descriptor_set_layout =
        new grassland::vulkan::DescriptorSetLayout(renderer->App()->VkCore(),
                                                   bindings);
    renderer->AddReleaseCallback([directional_light_descriptor_set_layout]() {
      delete directional_light_descriptor_set_layout;
    });
  }
  return directional_light_descriptor_set_layout;
}

grassland::vulkan::Pipeline *DirectionalLightPipeline(
    struct Renderer *renderer) {
  static std::map<Renderer *, PipelineAssets> ambient_light_pipelines;
  auto &pipeline = ambient_light_pipelines[renderer];
  if (!pipeline.pipeline) {
    pipeline.vertex_shader = new grassland::vulkan::ShaderModule(
        renderer->App()->VkCore(),
        BuiltInShaderSpv("fullscreen_lighting_pass.vert"));
    pipeline.fragment_shader = new grassland::vulkan::ShaderModule(
        renderer->App()->VkCore(), BuiltInShaderSpv("directional_light.frag"));

    pipeline.pipeline_layout = new grassland::vulkan::PipelineLayout(
        renderer->App()->VkCore(),
        std::vector<grassland::vulkan::DescriptorSetLayout *>{
            renderer->RenderPipeline()->LightingPassDescriptorSetLayout(),
            DirectionalLightDescriptorSetLayout(renderer)});

    grassland::vulkan::PipelineSettings directional_light_pipeline_settings(
        renderer->RenderPipeline()->RenderPass(), pipeline.pipeline_layout, 1);
    directional_light_pipeline_settings.AddShaderStage(
        pipeline.vertex_shader, VK_SHADER_STAGE_VERTEX_BIT);
    directional_light_pipeline_settings.AddShaderStage(
        pipeline.fragment_shader, VK_SHADER_STAGE_FRAGMENT_BIT);
    directional_light_pipeline_settings.SetPrimitiveTopology(
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

    directional_light_pipeline_settings.SetMultiSampleState(
        VK_SAMPLE_COUNT_1_BIT);

    directional_light_pipeline_settings.SetCullMode(VK_CULL_MODE_NONE);

    directional_light_pipeline_settings.SetBlendState(
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
        renderer->App()->VkCore(), directional_light_pipeline_settings);
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
