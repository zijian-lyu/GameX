#include "GameX/renderer/zbuffer.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"

namespace GameX::Base {
ZBuffer::ZBuffer(struct Renderer *renderer, int width, int height) {
  depth_image_ = std::make_unique<grassland::vulkan::Image>(
      renderer->App()->VkCore(), VK_FORMAT_D32_SFLOAT,
      VkExtent2D{static_cast<uint32_t>(width), static_cast<uint32_t>(height)},
      VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT |
          VK_IMAGE_USAGE_TRANSFER_DST_BIT);
}
}  // namespace GameX::Base
