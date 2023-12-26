#pragma once
#include "GameX/utils/utils.h"

namespace GameX::Graphics {
GAMEX_CLASS(Image) {
 public:
  Image(struct Renderer * renderer, const std::string &path);
  Image(struct Renderer * renderer, const Base::ImageHDR &image_hdr);
  Image(struct Renderer * renderer, const Base::Image &image);

  void Init(struct Renderer * renderer, const Base::ImageHDR &image_hdr);
  void Init(struct Renderer * renderer, const Base::Image &image);

  grassland::vulkan::Image *Handle() const {
    return image_.get();
  }

 private:
  std::unique_ptr<grassland::vulkan::Image> image_{};
};
}  // namespace GameX::Graphics
