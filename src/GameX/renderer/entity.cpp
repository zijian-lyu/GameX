#include "GameX/renderer/entity.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"
#include "GameX/renderer/scene.h"

namespace GameX::Base {
Entity::Entity(Scene *scene, const class Model *model) {
  scene_ = scene;
  model_ = model;

  entity_buffer_ =
      std::make_unique<grassland::vulkan::DynamicBuffer<EntitySettings>>(
          scene_->Renderer()->App()->Core(), 1,
          VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);

  entity_buffer_->At(0).model = glm::mat4(1.0f);

  scene_->Renderer()->RegisterSyncObject(entity_buffer_.get());

  descriptor_sets_.resize(
      scene_->Renderer()->App()->Core()->MaxFramesInFlight());

  for (size_t i = 0; i < descriptor_sets_.size(); ++i) {
    descriptor_sets_[i] = std::make_unique<grassland::vulkan::DescriptorSet>(
        scene_->Renderer()->App()->Core(), scene_->DescriptorPool(),
        scene_->Renderer()->EntityDescriptorSetLayout());

    VkDescriptorBufferInfo buffer_info = {};
    buffer_info.buffer = entity_buffer_->GetBuffer(i)->Handle();
    buffer_info.offset = 0;
    buffer_info.range = sizeof(EntitySettings);

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

Entity::~Entity() {
  scene_->Renderer()->UnregisterSyncObject(entity_buffer_.get());
  scene_->DestroyEntity(this);
}
}  // namespace GameX::Base
