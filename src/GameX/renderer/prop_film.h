#pragma once
#include "GameX/utils/utils.h"

namespace GameX {
class PropertyFilm {
 public:
  PropertyFilm(class Renderer renderer, uint32_t width, uint32_t height);

  grassland::vulkan::Image *AlbedoImage() const {
    return albedo_image_.get();
  }

  grassland::vulkan::Image *NormalImage() const {
    return normal_image_.get();
  }

  grassland::vulkan::Image *PositionImage() const {
    return position_image_.get();
  }

  grassland::vulkan::Image *IndexImage() const {
    return index_image_.get();
  }

  grassland::vulkan::Image *FlagImage() const {
    return flag_image_.get();
  }

  grassland::vulkan::Image *DepthImage() const {
    return depth_image_.get();
  }

  grassland::vulkan::Framebuffer *Framebuffer() const {
    return framebuffer_.get();
  }

 private:
  std::unique_ptr<grassland::vulkan::Image> albedo_image_;
  std::unique_ptr<grassland::vulkan::Image> normal_image_;
  std::unique_ptr<grassland::vulkan::Image> position_image_;
  std::unique_ptr<grassland::vulkan::Image> index_image_;
  std::unique_ptr<grassland::vulkan::Image> flag_image_;
  std::unique_ptr<grassland::vulkan::Image> depth_image_;
  std::unique_ptr<grassland::vulkan::Framebuffer> framebuffer_;
};
}  // namespace GameX
