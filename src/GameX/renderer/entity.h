#pragma once
#include "GameX/renderer/image.h"
#include "GameX/renderer/model.h"

namespace GameX::Graphics {
class Renderer;

GAMEX_CLASS(Entity) : public grassland::vulkan::DynamicObject {
 public:
  struct EntitySettings {
    glm::mat4 model;
  };

  Entity(class Scene * scene, const PModel model);

  ~Entity();

  grassland::vulkan::DescriptorSet *DescriptorSet(int frame_index) const {
    return descriptor_sets_[frame_index].get();
  }

  const PModel Model() const {
    return model_;
  }

  void SetAffineMatrix(const glm::mat4 &affine_matrix);

  void SetAlbedoImage(Image * image);

  void SetAlbedoImageSampler(Image * image,
                             grassland::vulkan::Sampler * sampler);

 private:
  bool SyncData(VkCommandBuffer cmd_buffer, uint32_t frame_index) override;

  Scene *scene_;
  PModel model_;
  std::unique_ptr<grassland::vulkan::DynamicBuffer<EntitySettings>>
      entity_buffer_;
  std::vector<std::unique_ptr<grassland::vulkan::DescriptorSet>>
      descriptor_sets_;

  PImage albedo_image_{};
  grassland::vulkan::Sampler *albedo_sampler_{};
  std::vector<uint64_t> albedo_image_versions_{};
  uint64_t staging_albedo_image_version_{0};
};

grassland::vulkan::DescriptorSetLayout *EntityDescriptorSetLayout(
    class Renderer *renderer);
}  // namespace GameX::Graphics
