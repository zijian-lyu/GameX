#pragma once

#include "GameX/utils/utils.h"

namespace GameX::Base {
class ZBuffer {
 public:
  ZBuffer() = default;
  ZBuffer(class Renderer *renderer, int width, int height);

  [[nodiscard]] grassland::vulkan::Image *DepthImage() const {
    return depth_image_.get();
  }

 private:
  std::unique_ptr<grassland::vulkan::Image> depth_image_;
};
}  // namespace GameX::Base
