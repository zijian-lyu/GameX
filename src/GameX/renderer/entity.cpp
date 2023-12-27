#include "GameX/renderer/entity.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"
#include "GameX/renderer/scene.h"

namespace GameX::Graphics {
Entity::Entity(Scene *scene, const PModel model) {
  scene_ = scene;
  model_ = model;

  entity_buffer_ =
      std::make_unique<grassland::vulkan::DynamicBuffer<EntitySettings>>(
          scene_->Renderer()->App()->VkCore(), 1,
          VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);

  entity_buffer_->At(0).model = glm::mat4(1.0f);

  scene_->Renderer()->RegisterSyncObject(entity_buffer_.get());

  albedo_image_versions_.resize(
      scene_->Renderer()->App()->VkCore()->MaxFramesInFlight(), 0);
  staging_albedo_image_version_ = 0;
  scene_->Renderer()->RegisterSyncObject(this);

  albedo_image_ = scene_->Renderer()->WhiteImage();
  albedo_sampler_ = scene_->Renderer()->LinearSampler();

  descriptor_sets_.resize(
      scene_->Renderer()->App()->VkCore()->MaxFramesInFlight());

  for (size_t i = 0; i < descriptor_sets_.size(); ++i) {
    descriptor_sets_[i] = std::make_unique<grassland::vulkan::DescriptorSet>(
        scene_->Renderer()->App()->VkCore(), scene_->DescriptorPool(),
        EntityDescriptorSetLayout(scene_->Renderer()));

    VkDescriptorBufferInfo buffer_info = {};
    buffer_info.buffer = entity_buffer_->GetBuffer(i)->Handle();
    buffer_info.offset = 0;
    buffer_info.range = sizeof(EntitySettings);

    std::vector<VkWriteDescriptorSet> write_descriptor_sets;

    {
      VkWriteDescriptorSet write_descriptor_set = {};
      write_descriptor_set.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
      write_descriptor_set.dstSet = descriptor_sets_[i]->Handle();
      write_descriptor_set.dstBinding = 0;
      write_descriptor_set.dstArrayElement = 0;
      write_descriptor_set.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
      write_descriptor_set.descriptorCount = 1;
      write_descriptor_set.pBufferInfo = &buffer_info;

      write_descriptor_sets.emplace_back(write_descriptor_set);
    }

    VkDescriptorImageInfo image_info = {};
    image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    image_info.imageView = albedo_image_->Handle()->ImageView();
    image_info.sampler = albedo_sampler_->Handle();

    {
      VkWriteDescriptorSet write_descriptor_set = {};
      write_descriptor_set.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
      write_descriptor_set.dstSet = descriptor_sets_[i]->Handle();
      write_descriptor_set.dstBinding = 1;
      write_descriptor_set.dstArrayElement = 0;
      write_descriptor_set.descriptorType =
          VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
      write_descriptor_set.descriptorCount = 1;
      write_descriptor_set.pImageInfo = &image_info;

      write_descriptor_sets.emplace_back(write_descriptor_set);
    }

    vkUpdateDescriptorSets(
        scene_->Renderer()->App()->VkCore()->Device()->Handle(),
        write_descriptor_sets.size(), write_descriptor_sets.data(), 0, nullptr);
  }
}

Entity::~Entity() {
  scene_->Renderer()->UnregisterSyncObject(entity_buffer_.get());
  scene_->Renderer()->UnregisterSyncObject(this);
  scene_->DestroyEntity(this);
}

void Entity::SetAffineMatrix(const glm::mat4 &affine_matrix) {
  entity_buffer_->At(0).model = affine_matrix;
}

bool Entity::SyncData(VkCommandBuffer cmd_buffer, uint32_t frame_index) {
  if (albedo_image_versions_[frame_index] != staging_albedo_image_version_) {
    VkDescriptorImageInfo image_info = {};
    image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    image_info.imageView = albedo_image_->Handle()->ImageView();
    image_info.sampler = albedo_sampler_->Handle();

    VkWriteDescriptorSet write_descriptor_set = {};
    write_descriptor_set.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_descriptor_set.dstSet = descriptor_sets_[frame_index]->Handle();
    write_descriptor_set.dstBinding = 1;
    write_descriptor_set.dstArrayElement = 0;
    write_descriptor_set.descriptorType =
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    write_descriptor_set.descriptorCount = 1;
    write_descriptor_set.pImageInfo = &image_info;

    vkUpdateDescriptorSets(
        scene_->Renderer()->App()->VkCore()->Device()->Handle(), 1,
        &write_descriptor_set, 0, nullptr);

    albedo_image_versions_[frame_index] = staging_albedo_image_version_;
    return true;
  }
  return false;
}

void Entity::SetAlbedoImage(Image *image) {
  SetAlbedoImageSampler(image, albedo_sampler_);
}

void Entity::SetAlbedoImageSampler(Image *image,
                                   grassland::vulkan::Sampler *sampler) {
  albedo_image_ = image;
  albedo_sampler_ = sampler;
  staging_albedo_image_version_++;
}

grassland::vulkan::DescriptorSetLayout *EntityDescriptorSetLayout(
    Renderer *renderer) {
  static std::map<Renderer *, grassland::vulkan::DescriptorSetLayout *>
      entity_descriptor_set_layouts;
  if (!entity_descriptor_set_layouts.count(renderer)) {
    grassland::vulkan::DescriptorSetLayout *&entity_descriptor_set_layout =
        entity_descriptor_set_layouts[renderer];
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    bindings.resize(2);
    bindings[0].binding = 0;
    bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    bindings[0].descriptorCount = 1;
    bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    bindings[0].pImmutableSamplers = nullptr;

    // TODO: Add texture sampler
    bindings[1].binding = 1;
    bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    bindings[1].descriptorCount = 1;
    bindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    bindings[1].pImmutableSamplers = nullptr;

    entity_descriptor_set_layout = new grassland::vulkan::DescriptorSetLayout(
        renderer->App()->VkCore(), bindings);
    renderer->AddReleaseCallback([entity_descriptor_set_layout]() {
      delete entity_descriptor_set_layout;
    });

    return entity_descriptor_set_layout;
  }
  return entity_descriptor_set_layouts.at(renderer);
}
}  // namespace GameX::Graphics
