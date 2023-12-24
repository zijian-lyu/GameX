#include "GameX/renderer/lights/directional_light.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"

namespace GameX {
DirectionalLight::DirectionalLight(Scene *scene,
                                   const DirectionalLightData &settings)
    : Light(scene) {
  buffer_ =
      std::make_unique<grassland::vulkan::DynamicBuffer<DirectionalLightData>>(
          scene_->Renderer()->App()->Core(), 1,
          VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);

  buffer_->At(0) = settings;

  scene_->Renderer()->RegisterSyncObject(buffer_.get());

  descriptor_sets_.resize(
      scene_->Renderer()->App()->Core()->MaxFramesInFlight());

  for (size_t i = 0; i < descriptor_sets_.size(); ++i) {
    descriptor_sets_[i] = std::make_unique<grassland::vulkan::DescriptorSet>(
        scene_->Renderer()->App()->Core(), scene_->DescriptorPool(),
        scene_->Renderer()->AmbientLightDescriptorSetLayout());

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
        scene_->Renderer()->App()->Core()->Device()->Handle(), 1,
        &write_descriptor_set, 0, nullptr);
  }
}

DirectionalLight::~DirectionalLight() {
  scene_->Renderer()->UnregisterSyncObject(buffer_.get());
}

grassland::vulkan::Pipeline *DirectionalLight::LightingPipeline() {
  return scene_->Renderer()->RenderPipeline()->DirectionalLightPipeline();
}

void DirectionalLight::Lighting(VkCommandBuffer cmd_buffer, int frame_index) {
  VkDescriptorSet descriptor_sets[] = {descriptor_sets_[frame_index]->Handle()};

  vkCmdBindDescriptorSets(
      cmd_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
      LightingPipeline()->Settings().pipeline_layout->Handle(), 1, 1,
      descriptor_sets, 0, nullptr);

  vkCmdDraw(cmd_buffer, 6, 1, 0, 0);
}
}  // namespace GameX
