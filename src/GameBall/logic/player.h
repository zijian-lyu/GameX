#pragma once
#include "GameBall/core/utils.h"

namespace GameBall::Logic {
class World;
class Player {
 public:
  Player(World *world);
  ~Player();
  uint64_t PlayerId() const;

  uint64_t PrimaryUnitId() const;

  void SetPrimaryUnit(uint64_t unit_id);

 private:
  World *world_;
  uint64_t player_id_{};

  uint64_t primary_unit_id_{};
};
}  // namespace GameBall::Logic
