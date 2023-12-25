#pragma once
#include "GameX/utils/utils.h"

namespace GameX::Base {
class Light {
 public:
  Light(class Scene *scene) : scene_(scene) {
  }

  virtual ~Light();

  virtual grassland::vulkan::Pipeline *LightingPipeline() = 0;

  virtual void Lighting(VkCommandBuffer cmd_buffer, int frame_index) = 0;

 protected:
  class Scene *scene_;
};
}  // namespace GameX::Base
