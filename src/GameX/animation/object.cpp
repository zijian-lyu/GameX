#include "GameX/animation/object.h"

#include "GameX/animation/manager.h"

namespace GameX::Animation {
Object::Object(class Manager *manager) {
  manager_ = manager;
  manager_->RegisterObject(this);
}

Object::~Object() = default;

void Object::Release() {
  manager_->UnregisterObject(this);
}
}  // namespace GameX::Animation
