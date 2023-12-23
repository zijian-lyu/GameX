#pragma once

#include "GameX/renderer/camera.h"
#include "GameX/renderer/entity.h"
#include "GameX/renderer/render_pipeline.h"

namespace GameX {

struct SceneSettings {
  int max_objects = 1000;
  int max_lights = 100;
  int max_cameras = 100;
};

class Scene {
 public:
  Scene(class Renderer *renderer, const SceneSettings &settings = {});

  class Renderer *Renderer() {
    return renderer_;
  }

  grassland::vulkan::DescriptorPool *DescriptorPool() {
    return descriptor_pool_.get();
  }

  template <class... Args>
  std::unique_ptr<Camera> CreateCamera(Args &&...args) {
    auto camera = std::make_unique<Camera>(this, std::forward<Args>(args)...);
    cameras_.insert(camera.get());
    return camera;
  }

  template <class... Args>
  std::unique_ptr<Entity> CreateEntity(Args &&...args) {
    auto entity = std::make_unique<Entity>(this, std::forward<Args>(args)...);
    entities_.insert(entity.get());
    return entity;
  }

  void DestroyCamera(Camera *camera) {
    cameras_.erase(camera);
  }

  void DestroyEntity(Entity *entity) {
    entities_.erase(entity);
  }

  const std::set<Entity *> &Entities() const {
    return entities_;
  }

 private:
  class Renderer *renderer_;
  std::unique_ptr<grassland::vulkan::DescriptorPool> descriptor_pool_;
  std::set<Camera *> cameras_;
  std::set<Entity *> entities_;
};
}  // namespace GameX
