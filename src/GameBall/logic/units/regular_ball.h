#pragma once
#include "GameBall/core/actors/common_ball_actor.h"
#include "GameBall/logic/unit.h"

namespace GameBall::Logic::Units {
class RegularBall : public Unit {
 public:
  RegularBall(World *world, uint64_t player_id);
  ~RegularBall();

  SYNC_ACTOR_FUNC_DECLARE(Actors::CommonBallActor)

 private:
};
}  // namespace GameBall::Logic::Units
