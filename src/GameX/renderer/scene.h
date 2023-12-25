#pragma once

#include "GameX/renderer/camera.h"
#include "GameX/renderer/entity.h"
#include "GameX/renderer/light.h"
#include "GameX/renderer/render_pipeline.h"

namespace GameX::Base {

struct SceneSettings {
  int max_objects = 1000;
  int max_ambient_light = 100;
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

  template <class LightType, class... Args>
  std::unique_ptr<LightType> CreateLight(Args &&...args) {
    auto light = std::make_unique<LightType>(this, std::forward<Args>(args)...);
    lights_.insert(light.get());
    return light;
  }

  void DestroyCamera(Camera *camera) {
    cameras_.erase(camera);
  }

  void DestroyEntity(Entity *entity) {
    entities_.erase(entity);
  }

  void DestroyLight(Light *light) {
    lights_.erase(light);
  }

  const std::set<Entity *> &Entities() const {
    return entities_;
  }

  const std::set<Light *> &Lights() const {
    return lights_;
  }

 private:
  class Renderer *renderer_;
  std::unique_ptr<grassland::vulkan::DescriptorPool> descriptor_pool_;
  std::set<Camera *> cameras_;
  std::set<Entity *> entities_;
  std::set<Light *> lights_;
};
}  // namespace GameX::Base
