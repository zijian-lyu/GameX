#pragma once
#include "GameX/utils/utils.h"

namespace GameX {
class PropertyFilm {
 public:
  PropertyFilm(class Renderer renderer, uint32_t width, uint32_t height);

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
