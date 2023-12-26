#pragma once
#include "GameX/utils/utils.h"

namespace GameX::Graphics {
class Renderer;
class Texture {
 public:
  Texture() = default;

  Texture(Renderer *renderer, int width, int height);

  void Init(Renderer *renderer, int width, int height);

  [[nodiscard]] grassland::vulkan::Image *Image() const {
    return image_.get();
  }

 private:
  std::unique_ptr<grassland::vulkan::Image> image_;
};
}  // namespace GameX::Graphics
