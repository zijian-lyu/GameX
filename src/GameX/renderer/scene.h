#pragma once

#include "GameX/renderer/object.h"

namespace GameX {
class Scene {
 public:
  Scene(Renderer *renderer) : renderer_(renderer) {
  }

  grassland::vulkan::DescriptorPool *DescriptorPool() {
    return descriptor_pool_.get();
  }

 private:
  Renderer *renderer_;
  std::unique_ptr<grassland::vulkan::DescriptorPool> descriptor_pool_;
};
}  // namespace GameX
