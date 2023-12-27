#pragma once
#include "GameBall/core/utils.h"

namespace GameBall::Logic {
class World;
class Player {
 public:
  Player(World *world);
  ~Player();
  uint64_t PlayerId() const;

 private:
  World *world_;
  uint64_t player_id_{};
};
}  // namespace GameBall::Logic
