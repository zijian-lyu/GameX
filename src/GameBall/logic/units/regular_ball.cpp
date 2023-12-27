#include "GameBall/logic/units/regular_ball.h"

#include "GameBall/core/game_ball.h"
#include "GameBall/logic/world.h"

namespace GameBall::Logic::Units {
RegularBall::RegularBall(World *world,
                         uint64_t player_id,
                         const glm::vec3 &position,
                         float scale,
                         float weight,
                         float J)
    : Unit(world, player_id) {
  scale_ = scale;
  weight_ = weight;
  position_ = position;
  L_ = glm::vec3{0.0f};
  J_ = J;
}

RegularBall::~RegularBall() {
  ;
}

SYNC_ACTOR_FUNC(RegularBall) {
  actor->SetWeight(1.0f);
  actor->SetGravity(glm::vec3{0.0f, -9.8f, 0.0f});
  actor->SetTransform(glm::mat3{scale_});
  actor->SetMotion(position_, velocity_, rotation_, L_);
  actor->SetMomentOfInertia(J_);
}

void RegularBall::UpdateTick() {
  auto delta_time = world_->TickDeltaT();
  glm::vec3 acceleration = glm::vec3{0.0f, -9.8f, 0.0f};
  velocity_ += acceleration * delta_time;
  position_ += velocity_ * delta_time;

  glm::vec3 omega = L_ / J_;

  float theta = glm::length(omega) * delta_time;
  if (theta > 0.0f) {
    rotation_ =
        glm::mat3{glm::rotate(glm::mat4{1.0f}, theta, omega)} * rotation_;
  }
}
}  // namespace GameBall::Logic::Units
