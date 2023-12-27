#pragma once
#include "GameBall/core/actor.h"

namespace GameBall {
class CommonBallActor : public Actor {
 public:
  CommonBallActor(GameBall *app);
  ~CommonBallActor();

 private:
  GameX::Graphics::UStaticModel model_;
  GameX::Graphics::UEntity entity_;
};
}  // namespace GameBall
