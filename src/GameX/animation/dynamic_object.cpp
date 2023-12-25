#include "GameX/animation/dynamic_object.h"

#include "GameX/animation/manager.h"

namespace GameX::Animation {
DynamicObject::DynamicObject(class Manager *manager) : Object(manager) {
  manager_->RegisterDynamicObject(this);
}

DynamicObject::~DynamicObject() {
  manager_->UnregisterDynamicObject(this);
}
}  // namespace GameX::Animation
