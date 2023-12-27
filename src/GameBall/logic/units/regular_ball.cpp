#include "GameBall/logic/units/regular_ball.h"

#include "GameBall/core/game_ball.h"
#include "GameBall/logic/world.h"

namespace GameBall::Logic::Units {

RegularBall::RegularBall(World *world, uint64_t player_id)
    : Unit(world, player_id) {
  ;
}

RegularBall::~RegularBall() {
  ;
}

SYNC_ACTOR_FUNC(RegularBall) {
}
}  // namespace GameBall::Logic::Units
