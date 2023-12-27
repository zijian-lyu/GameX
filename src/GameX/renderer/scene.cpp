#include "GameX/renderer/scene.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"

namespace GameX::Graphics {
Scene::Scene(class Renderer *renderer, const SceneSettings &settings) {
  renderer_ = renderer;
  grassland::vulkan::DescriptorPoolSettings descriptor_pool_settings;

  descriptor_pool_ = std::make_unique<grassland::vulkan::DescriptorPool>(
      renderer_->App()->VkCore(), descriptor_pool_settings);

  renderer_->RegisterSyncObject(this);

  envmap_versions_.resize(renderer_->App()->VkCore()->MaxFramesInFlight(), 0);
  staging_envmap_version_ = 0;

  envmap_sampler_ = renderer_->LinearSampler();
  envmap_image_ = renderer_->WhiteImage();

  envmap_data_buffer_ =
      std::make_unique<grassland::vulkan::DynamicBuffer<EnvmapData>>(
          renderer_->App()->VkCore(), 1, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
  renderer_->RegisterSyncObject(envmap_data_buffer_.get());
  envmap_data_buffer_->At(0) = EnvmapData{0.0f, 1.0f};
  envmap_descriptor_sets_.resize(
      renderer_->App()->VkCore()->MaxFramesInFlight());
  for (int i = 0; i < renderer_->App()->VkCore()->MaxFramesInFlight(); ++i) {
    envmap_descriptor_sets_[i] =
        std::make_unique<grassland::vulkan::DescriptorSet>(
            renderer_->App()->VkCore(), descriptor_pool_.get(),
            EnvmapDescriptorSetLayout(renderer_));
    VkDescriptorBufferInfo buffer_info{};
    buffer_info.buffer = envmap_data_buffer_->GetBuffer(i)->Handle();
    buffer_info.offset = 0;
    buffer_info.range = sizeof(EnvmapData);
    VkDescriptorImageInfo image_info{};
    image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    image_info.imageView = envmap_image_->Handle()->ImageView();
    image_info.sampler = envmap_sampler_->Handle();
    std::vector<VkWriteDescriptorSet> writes(2);
    writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[0].pNext = nullptr;
    writes[0].dstSet = envmap_descriptor_sets_[i]->Handle();
    writes[0].dstBinding = 0;
    writes[0].dstArrayElement = 0;
    writes[0].descriptorCount = 1;
    writes[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    writes[0].pImageInfo = nullptr;
    writes[0].pBufferInfo = &buffer_info;
    writes[0].pTexelBufferView = nullptr;
    writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[1].pNext = nullptr;
    writes[1].dstSet = envmap_descriptor_sets_[i]->Handle();
    writes[1].dstBinding = 1;
    writes[1].dstArrayElement = 0;
    writes[1].descriptorCount = 1;
    writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[1].pImageInfo = &image_info;
    writes[1].pBufferInfo = nullptr;
    writes[1].pTexelBufferView = nullptr;
    vkUpdateDescriptorSets(renderer_->App()->VkCore()->Device()->Handle(),
                           static_cast<uint32_t>(writes.size()), writes.data(),
                           0, nullptr);
  }
}

Scene::~Scene() {
  renderer_->UnregisterSyncObject(this);
}

bool Scene::SyncData(VkCommandBuffer cmd_buffer, uint32_t frame_index) {
  if (staging_envmap_version_ != envmap_versions_[frame_index]) {
    VkDescriptorImageInfo image_info{};
    image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    image_info.imageView = envmap_image_->Handle()->ImageView();
    image_info.sampler = envmap_sampler_->Handle();
    VkWriteDescriptorSet write{};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.pNext = nullptr;
    write.dstSet = envmap_descriptor_sets_[frame_index]->Handle();
    write.dstBinding = 1;
    write.dstArrayElement = 0;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    write.pImageInfo = &image_info;
    write.pBufferInfo = nullptr;
    write.pTexelBufferView = nullptr;
    vkUpdateDescriptorSets(renderer_->App()->VkCore()->Device()->Handle(), 1,
                           &write, 0, nullptr);
    envmap_versions_[frame_index] = staging_envmap_version_;
  }
  return false;
}

grassland::vulkan::DescriptorSetLayout *EnvmapDescriptorSetLayout(
    struct Renderer *renderer) {
  static std::map<Renderer *, grassland::vulkan::DescriptorSetLayout *>
      envmap_descriptor_set_layouts;
  auto &envmap_descriptor_set_layout = envmap_descriptor_set_layouts[renderer];
  if (!envmap_descriptor_set_layout) {
    std::vector<VkDescriptorSetLayoutBinding> bindings(2);
    bindings[0].binding = 0;
    bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    bindings[0].descriptorCount = 1;
    bindings[0].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    bindings[0].pImmutableSamplers = nullptr;
    bindings[1].binding = 1;
    bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    bindings[1].descriptorCount = 1;
    bindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    bindings[1].pImmutableSamplers = nullptr;

    envmap_descriptor_set_layout = new grassland::vulkan::DescriptorSetLayout(
        renderer->App()->VkCore(), bindings);
    renderer->AddReleaseCallback([envmap_descriptor_set_layout]() {
      delete envmap_descriptor_set_layout;
    });
  }
  return envmap_descriptor_set_layout;
}
}  // namespace GameX::Graphics
