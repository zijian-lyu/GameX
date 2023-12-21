#include "GameX/renderer/prop_film.h"

#include "GameX/renderer/renderer.h"

namespace GameX {
PropertyFilm::PropertyFilm(Renderer renderer, uint32_t width, uint32_t height) {
  auto core = renderer.App()->Core();
  VkExtent2D extent = {width, height};
  albedo_image_ = std::make_unique<grassland::vulkan::Image>(
      core, VK_FORMAT_R32G32B32_SFLOAT, extent,
      VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
  normal_image_ = std::make_unique<grassland::vulkan::Image>(
      core, VK_FORMAT_R32G32B32_SFLOAT, extent,
      VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
  position_image_ = std::make_unique<grassland::vulkan::Image>(
      core, VK_FORMAT_R32G32B32_SFLOAT, extent,
      VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
  index_image_ = std::make_unique<grassland::vulkan::Image>(
      core, VK_FORMAT_R32_UINT, extent,
      VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
  flag_image_ = std::make_unique<grassland::vulkan::Image>(
      core, VK_FORMAT_R32_UINT, extent,
      VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
  depth_image_ = std::make_unique<grassland::vulkan::Image>(
      core, VK_FORMAT_D32_SFLOAT, extent,
      VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
      VK_IMAGE_ASPECT_DEPTH_BIT);

  std::vector<VkImageView> attachments = {
      albedo_image_->ImageView(),   normal_image_->ImageView(),
      position_image_->ImageView(), index_image_->ImageView(),
      flag_image_->ImageView(),     depth_image_->ImageView()};

  framebuffer_ = std::make_unique<grassland::vulkan::Framebuffer>(
      core, extent, renderer.PropertyFilmRenderPass()->Handle(), attachments);
}
}  // namespace GameX
