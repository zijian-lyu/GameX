#include "GameX/core/object.h"

#include "GameX/core/core.h"
#include "GameX/core/object_manager.h"

namespace GameX::Base {
Object::Object(class Core *core) : Object(core, core) {
}

Object::Object(class Core *core, class ObjectManager *superior)
    : core_(core), superior_(superior) {
  if (superior_) {
    superior_->RegisterSubordinate(this);
  }
}

Object::~Object() {
  if (superior_) {
    superior_->UnregisterSubordinate(this);
  }
}

void Object::Depend(Object *dependency) {
  if (superior_) {
    superior_->RegisterDependency(this, dependency);
  }
}

void Object::Undepend(Object *dependency) {
  if (superior_) {
    superior_->UnregisterDependency(this, dependency);
  }
}
}  // namespace GameX::Base
