#include "GameBall/logic/player.h"

#include "GameBall/logic/world.h"

namespace GameBall::Logic {

Player::Player(World *world) : world_(world) {
  player_id_ = world_->RegisterPlayer(this);
}

uint64_t Player::PlayerId() const {
  return player_id_;
}
}  // namespace GameBall::Logic
