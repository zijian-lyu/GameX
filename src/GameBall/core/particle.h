#pragma once
#include "GameBall/core/utils.h"

namespace GameBall {
class GameBall;
class Particle {
 public:
  Particle(GameBall *app);
  bool Update(float delta_time);

 private:
};
}  // namespace GameBall
