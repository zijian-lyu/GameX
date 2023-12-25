#pragma once
#include <map>
#include <set>

#include "GameX/utils/utils.h"

namespace GameX::Base {
class Object {
 public:
  Object(class Core *core);
  Object(class Core *core, class ObjectManager *superior);

  virtual ~Object();

  virtual void Update() = 0;

  void Depend(Object *dependency);

  void Undepend(Object *dependency);

 protected:
  class Core *core_{};
  class ObjectManager *superior_{};
};
}  // namespace GameX::Base
