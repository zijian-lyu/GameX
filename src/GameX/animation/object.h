#pragma once
#include "GameX/animation/common.h"

namespace GameX::Animation {
class Object {
 public:
  Object(class Manager *manager);
  virtual ~Object();
  void Release();

 protected:
  class Manager *manager_;
};
}  // namespace GameX::Animation
