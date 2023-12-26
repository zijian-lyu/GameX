#pragma once
#include "GameX/renderer/model.h"

namespace GameX::Graphics {
class Renderer;

GAMEX_CLASS(Entity) {
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

 private:
  Scene *scene_;
  PModel model_;
  std::unique_ptr<grassland::vulkan::DynamicBuffer<EntitySettings>>
      entity_buffer_;
  std::vector<std::unique_ptr<grassland::vulkan::DescriptorSet>>
      descriptor_sets_;
};
}  // namespace GameX::Graphics
