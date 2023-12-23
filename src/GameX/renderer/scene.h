#pragma once

#include "GameX/renderer/model.h"

namespace GameX {

struct SceneSettings {
  int max_objects = 1000;
  int max_lights = 100;
  int max_cameras = 100;
};

class Scene {
 public:
  Scene(Renderer *renderer, const SceneSettings &settings = {});

  Renderer *Renderer() {
    return renderer_;
  }

  grassland::vulkan::DescriptorPool *DescriptorPool() {
    return descriptor_pool_.get();
  }

  grassland::vulkan::DescriptorSetLayout *CameraDescriptorSetLayout() {
    return camera_descriptor_set_layout_.get();
  }

 private:
  void CreateCameraSetLayout();

  class Renderer *renderer_;
  std::unique_ptr<grassland::vulkan::DescriptorPool> descriptor_pool_;
  std::unique_ptr<grassland::vulkan::DescriptorSetLayout>
      camera_descriptor_set_layout_;
};
}  // namespace GameX
