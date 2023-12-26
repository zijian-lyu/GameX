#include "GameX/utils/image.h"

#include "GameX/utils/asset_probe.h"

// Include std_image and std_image_write and enable implementation
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

namespace GameX::Base {
Image::Image(const std::string &path) {
  auto real_path = AssetProbe::PublicInstance()->ProbeAsset(path);
  int width, height, channels;
  stbi_uc *pixels =
      stbi_load(real_path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
  if (!pixels) {
    LAND_ERROR("Failed to load image: {}", real_path);
  }
  width_ = width;
  height_ = height;
  pixels_.resize(width * height);
  memcpy(pixels_.data(), pixels, width * height * 4);
  stbi_image_free(pixels);
}

Image::Image(uint32_t width,
             uint32_t height,
             const std::vector<uint8_t> &pixels)
    : width_(width), height_(height) {
  pixels_.resize(width * height);
  memcpy(pixels_.data(), pixels.data(), pixels.size());
}

Image::Image(uint32_t width, uint32_t height, Pixel pixel)
    : width_(width), height_(height) {
  pixels_.resize(width * height);
  for (auto &p : pixels_) {
    p = pixel;
  }
}

void Image::Store(const std::string &path) {
  // auto recognize extension name
  auto ext = path.substr(path.find_last_of('.') + 1);
  if (ext == "png") {
    stbi_write_png(path.c_str(), width_, height_, 4, pixels_.data(),
                   width_ * 4);
  } else if (ext == "jpg" || ext == "jpeg") {
    stbi_write_jpg(path.c_str(), width_, height_, 4, pixels_.data(), 100);
  } else if (ext == "bmp") {
    stbi_write_bmp(path.c_str(), width_, height_, 4, pixels_.data());
  } else if (ext == "tga") {
    stbi_write_tga(path.c_str(), width_, height_, 4, pixels_.data());
  } else {
    LAND_ERROR("Unsupported image format: {}", ext);
  }
}

Image::Image(const ImageHDR &image_hdr) {
  width_ = image_hdr.width_;
  height_ = image_hdr.height_;
  pixels_.resize(width_ * height_);
  for (int i = 0; i < width_ * height_; ++i) {
    pixels_[i].r = static_cast<uint8_t>(
        std::clamp(image_hdr.pixels_[i].r, 0.0f, 1.0f) * 255.0f);
    pixels_[i].g = static_cast<uint8_t>(
        std::clamp(image_hdr.pixels_[i].g, 0.0f, 1.0f) * 255.0f);
    pixels_[i].b = static_cast<uint8_t>(
        std::clamp(image_hdr.pixels_[i].b, 0.0f, 1.0f) * 255.0f);
    pixels_[i].a = static_cast<uint8_t>(
        std::clamp(image_hdr.pixels_[i].a, 0.0f, 1.0f) * 255.0f);
  }
}

ImageHDR::ImageHDR(const std::string &path) {
  auto real_path = AssetProbe::PublicInstance()->ProbeAsset(path);
  int width, height, channels;
  float *pixels =
      stbi_loadf(real_path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
  if (!pixels) {
    LAND_ERROR("Failed to load image: {}", real_path);
  }
  width_ = width;
  height_ = height;
  pixels_.resize(width * height);
  memcpy(pixels_.data(), pixels, width * height * 4 * sizeof(float));
  stbi_image_free(pixels);
}

ImageHDR::ImageHDR(uint32_t width,
                   uint32_t height,
                   const std::vector<float> &pixels)
    : width_(width), height_(height) {
  pixels_.resize(width * height);
  memcpy(pixels_.data(), pixels.data(), pixels.size() * sizeof(float));
}

ImageHDR::ImageHDR(uint32_t width, uint32_t height, PixelHDR pixel)
    : width_(width), height_(height) {
  pixels_.resize(width * height);
  for (auto &p : pixels_) {
    p = pixel;
  }
}

void ImageHDR::Store(const std::string &path) {
  // auto recognize extension name
  auto ext = path.substr(path.find_last_of('.') + 1);
  if (ext == "hdr") {
    stbi_write_hdr(path.c_str(), width_, height_, 4,
                   reinterpret_cast<float *>(pixels_.data()));
  } else {
    LAND_ERROR("Unsupported image format: {}", ext);
  }
}
}  // namespace GameX::Base
