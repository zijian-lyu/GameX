#include "GameBall/core/actor.h"

namespace GameBall {
Actor::Actor(GameBall *app) : app_(app) {
}

Actor::~Actor() {
}

uint64_t Actor::SyncedLogicWorldVersion() const {
  return synced_logic_world_version_;
}

glm::vec3 Actor::Position() const {
  return position_;
}

glm::mat3 Actor::Rotation() const {
  return rotation_;
}
}  // namespace GameBall
