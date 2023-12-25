#pragma once

#include "GameX/core/object.h"
#include "GameX/core/object_manager.h"

namespace GameX::Base {
class Module : public Object, public ObjectManager {
 public:
  Module(class Core *core);
};
}  // namespace GameX::Base
