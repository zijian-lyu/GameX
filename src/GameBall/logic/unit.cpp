#include "GameBall/logic/unit.h"

#include "GameBall/logic/world.h"

namespace GameBall::Logic {
Unit::Unit(World *world) : Object(world) {
  unit_id_ = world_->RegisterUnit(this);
}

Unit::~Unit() {
  world_->UnregisterUnit(unit_id_);
}

uint64_t Unit::UnitId() const {
  return unit_id_;
}
}  // namespace GameBall::Logic
