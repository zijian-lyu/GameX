#pragma once
#include <map>
#include <set>

#include "GameX/utils/utils.h"

namespace GameX::Base {
class Object {
 public:
  Object(class Core *core_);
  Object(class Core *core_, class Module *superior);

  virtual ~Object();

  virtual void Update() = 0;

  void Depend(Object *dependency);

  void Undepend(Object *dependency);

 protected:
  class Core *core_{};
  class Module *superior_{};
};
}  // namespace GameX::Base
