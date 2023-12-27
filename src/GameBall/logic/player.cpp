#include "GameBall/logic/player.h"

#include "GameBall/logic/world.h"

namespace GameBall::Logic {

Player::Player(World *world) : world_(world) {
  player_id_ = world_->RegisterPlayer(this);
}

Player::~Player() {
  world_->UnregisterPlayer(player_id_);
}

uint64_t Player::PlayerId() const {
  return player_id_;
}

uint64_t Player::PrimaryUnitId() const {
  return primary_unit_id_;
}

void Player::SetPrimaryUnit(uint64_t unit_id) {
}
}  // namespace GameBall::Logic
