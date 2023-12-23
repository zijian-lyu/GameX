#pragma once
#include "GameX/renderer/model.h"

namespace GameX {
class Renderer;
class Entity {
 public:
  struct EntitySettings {
    glm::mat4 model;
  };

  Entity(class Scene *scene, const class Model *model);

  ~Entity();

 private:
  class Scene *scene_;
  const class Model *model_;
  std::unique_ptr<grassland::vulkan::DynamicBuffer<EntitySettings>>
      entity_buffer_;
  std::vector<std::unique_ptr<grassland::vulkan::DescriptorSet>>
      descriptor_sets_;
};
}  // namespace GameX
