#pragma once
#include "GameX/animation/object.h"

namespace GameX::Animation {
class DynamicObject : public Object {
 public:
  DynamicObject(class Manager *manager);
  virtual ~DynamicObject();
  virtual void Update(float delta_time) = 0;

 private:
};
}  // namespace GameX::Animation
