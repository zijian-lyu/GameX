#pragma once

#include "GameBall/core/actors/common_ball_actor.h"
#include "GameBall/logic/unit.h"

namespace GameBall::Logic::Units {
class RegularBall : public Unit {
 public:
  RegularBall(World *world,
              uint64_t player_id,
              const glm::vec3 &position,
              float scale = 1.0f,
              float weight = 1.0f,
              float J = 1.0f);

  ~RegularBall();

  SYNC_ACTOR_FUNC_DECLARE(Actors::CommonBallActor)

  void UpdateTick() override;

 private:
  float scale_{1.0f};
  float weight_{1.0f};
  glm::vec3 position_{};
  glm::vec3 velocity_{};
  glm::mat3 rotation_{1.0f};
  glm::vec3 L_{};
  float J_{1.0f};  // moment of inertia
};
}  // namespace GameBall::Logic::Units
