#pragma once
#include <map>
#include <set>

#include "GameX/utils/utils.h"

namespace GameX::Base {
class Object {
 public:
  Object();
  Object(struct ObjectManager *superior);

  virtual ~Object();

  virtual void Update() = 0;

  void Depend(Object *dependency);

  void Undepend(Object *dependency);

 protected:
  class ObjectManager *superior_{};
};
}  // namespace GameX::Base
