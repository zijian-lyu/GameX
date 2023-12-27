#pragma once
#include "GameBall/core/actor.h"

namespace GameBall::Actors {
class CommonBallActor : public Actor {
 public:
  CommonBallActor(GameBall *app);
  ~CommonBallActor();

  void Update(float delta_time) override;

 private:
  GameX::Graphics::UEntity entity_;
};
}  // namespace GameBall::Actors
