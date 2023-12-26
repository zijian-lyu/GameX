#include "GameX/renderer/image.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"

namespace GameX::Graphics {
Image::Image(struct Renderer *renderer, const std::string &path) {
  // recognize extension name
  std::string ext = path.substr(path.find_last_of('.') + 1);
  if (ext == "hdr") {
    Base::ImageHDR image_hdr(path);
    Init(renderer, image_hdr);
  } else {
    Base::Image image(path);
    Init(renderer, image);
  }
}

void Image::Init(struct Renderer *renderer, const Base::ImageHDR &image_hdr) {
  image_ = std::make_unique<grassland::vulkan::Image>(
      renderer->App()->VkCore(), VK_FORMAT_R32G32B32A32_SFLOAT,
      VkExtent2D{static_cast<uint32_t>(image_hdr.width_),
                 static_cast<uint32_t>(image_hdr.height_)});
  grassland::vulkan::Buffer staging_buffer(
      renderer->App()->VkCore(),
      image_hdr.pixels_.size() * sizeof(Base::PixelHDR),
      VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_AUTO_PREFER_HOST,
      VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT);
  std::memcpy(staging_buffer.Map(), image_hdr.pixels_.data(),
              image_hdr.pixels_.size() * sizeof(Base::PixelHDR));
  staging_buffer.Unmap();
  renderer->App()->VkCore()->SingleTimeCommands([&](VkCommandBuffer
                                                        command_buffer) {
    grassland::vulkan::TransitImageLayout(
        command_buffer, image_->Handle(), VK_IMAGE_LAYOUT_UNDEFINED,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_ACCESS_NONE, VK_ACCESS_TRANSFER_WRITE_BIT,
        VK_IMAGE_ASPECT_COLOR_BIT);
    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    region.imageOffset = {0, 0, 0};
    region.imageExtent = {image_->Extent().width, image_->Extent().height, 1};
    vkCmdCopyBufferToImage(command_buffer, staging_buffer.Handle(),
                           image_->Handle(),
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    grassland::vulkan::TransitImageLayout(
        command_buffer, image_->Handle(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
        VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT,
        VK_IMAGE_ASPECT_COLOR_BIT);
  });
}

void Image::Init(struct Renderer *renderer, const Base::Image &image) {
  image_ = std::make_unique<grassland::vulkan::Image>(
      renderer->App()->VkCore(), VK_FORMAT_R8G8B8A8_UNORM,
      VkExtent2D{static_cast<uint32_t>(image.width_),
                 static_cast<uint32_t>(image.height_)});
  grassland::vulkan::Buffer staging_buffer(
      renderer->App()->VkCore(), image.pixels_.size() * sizeof(Base::Pixel),
      VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_AUTO_PREFER_HOST,
      VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT);
  std::memcpy(staging_buffer.Map(), image.pixels_.data(),
              image.pixels_.size() * sizeof(Base::Pixel));
  staging_buffer.Unmap();
  renderer->App()->VkCore()->SingleTimeCommands([&](VkCommandBuffer
                                                        command_buffer) {
    grassland::vulkan::TransitImageLayout(
        command_buffer, image_->Handle(), VK_IMAGE_LAYOUT_UNDEFINED,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
        VK_ACCESS_NONE, VK_ACCESS_TRANSFER_WRITE_BIT,
        VK_IMAGE_ASPECT_COLOR_BIT);
    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    region.imageOffset = {0, 0, 0};
    region.imageExtent = {image_->Extent().width, image_->Extent().height, 1};
    vkCmdCopyBufferToImage(command_buffer, staging_buffer.Handle(),
                           image_->Handle(),
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    grassland::vulkan::TransitImageLayout(
        command_buffer, image_->Handle(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
        VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT,
        VK_IMAGE_ASPECT_COLOR_BIT);
  });
}

Image::Image(struct Renderer *renderer, const Base::ImageHDR &image_hdr) {
  Init(renderer, image_hdr);
}

Image::Image(struct Renderer *renderer, const Base::Image &image) {
  Init(renderer, image);
}
}  // namespace GameX::Graphics
