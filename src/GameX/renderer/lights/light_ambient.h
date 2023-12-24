#pragma once
#include "GameX/utils/utils.h"

namespace GameX {
class LightAmbient {
 public:
  struct LightAmbientSettings {
    glm::vec3 color;
    float intensity;
  };

  LightAmbient(const LightAmbientSettings &settings = {});

  const LightAmbientSettings &Settings() const {
    return settings_;
  }

  void SetSettings(const LightAmbientSettings &settings) {
    settings_ = settings;
  }

 private:
  LightAmbientSettings settings_;
};
}  // namespace GameX
