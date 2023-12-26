#pragma once
#include "GameX/utils/utils.h"

namespace GameX::Graphics {
GAMEX_DECLARE_CLASS(Scene)
GAMEX_CLASS(Light) {
 public:
  Light(PScene scene) : scene_(scene) {
  }

  virtual ~Light();

  virtual grassland::vulkan::Pipeline *LightingPipeline() = 0;

  virtual void Lighting(VkCommandBuffer cmd_buffer, int frame_index) = 0;

 protected:
  PScene scene_;
};
}  // namespace GameX::Graphics
