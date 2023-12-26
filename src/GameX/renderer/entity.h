#pragma once
#include "GameX/renderer/model.h"

namespace GameX::Graphics {
class Renderer;
class Entity {
 public:
  struct EntitySettings {
    glm::mat4 model;
  };

  Entity(class Scene *scene, const class Model *model);

  ~Entity();

  grassland::vulkan::DescriptorSet *DescriptorSet(int frame_index) const {
    return descriptor_sets_[frame_index].get();
  }

  const class Model *Model() const {
    return model_;
  }

  void SetEntitySettings(const EntitySettings &settings) {
    entity_buffer_->At(0) = settings;
  }

 private:
  class Scene *scene_;
  const class Model *model_;
  std::unique_ptr<grassland::vulkan::DynamicBuffer<EntitySettings>>
      entity_buffer_;
  std::vector<std::unique_ptr<grassland::vulkan::DescriptorSet>>
      descriptor_sets_;
};
}  // namespace GameX::Graphics
