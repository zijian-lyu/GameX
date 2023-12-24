#pragma once
#include "GameX/utils/utils.h"

namespace GameX {
class Light {
 public:
  Light(class Scene *scene) : scene_(scene) {
  }
  virtual ~Light() = default;

 private:
  class Scene *scene_;
};
}  // namespace GameX
