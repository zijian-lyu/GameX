#include "GameBall/core/actor.h"

namespace GameBall {
Actor::Actor(GameBall *app) : app_(app) {
}

Actor::~Actor() {
}

uint64_t Actor::SyncedLogicWorldVersion() const {
  return synced_logic_world_version_;
}
}  // namespace GameBall
