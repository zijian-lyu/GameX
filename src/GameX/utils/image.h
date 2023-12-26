#pragma once
#include "GameX/utils/common.h"

namespace GameX::Base {

struct ImageHDR;

struct Image {
  struct Pixel {
    uint8_t r, g, b, a;
  };

  Image(const std::string &path);
  Image(const ImageHDR &image_hdr);
  Image(uint32_t width, uint32_t height, const std::vector<uint8_t> &pixels);
  Image(uint32_t width, uint32_t height, Pixel pixel);

  uint32_t width_, height_;
  std::vector<Pixel> pixels_;

  void Store(const std::string &path);
};

typedef Image::Pixel Pixel;

struct ImageHDR {
  struct Pixel {
    float r, g, b, a;
  };

  ImageHDR(const std::string &path);
  ImageHDR(uint32_t width, uint32_t height, const std::vector<float> &pixels);
  ImageHDR(uint32_t width, uint32_t height, Pixel pixel);

  uint32_t width_, height_;
  std::vector<Pixel> pixels_;

  void Store(const std::string &path);
};

typedef ImageHDR::Pixel PixelHDR;
}  // namespace GameX::Base
