#include "GameX/utils/object.h"

#include "GameX/utils/object_manager.h"

namespace GameX::Base {
Object::Object() : Object(nullptr) {
}

Object::Object(struct ObjectManager *superior) : superior_(superior) {
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
