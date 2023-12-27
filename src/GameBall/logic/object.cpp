#include "GameBall/logic/object.h"

#include "GameBall/logic/world.h"

namespace GameBall::Logic {
Object::Object(World *world) : world_(world) {
  object_id_ = world_->RegisterObject(this);
}

Object::~Object() {
  world_->UnregisterObject(object_id_);
}

uint64_t Object::ObjectId() const {
  return object_id_;
}

void Object::UpdateTick() {
}

bool Object::ActorInitialize() const {
  return actor_initialize_;
}
}  // namespace GameBall::Logic
