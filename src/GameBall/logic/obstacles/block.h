#pragma once
#include "GameBall/logic/obstacle.h"

namespace GameBall::Logic {
class Block : public Obstacle {
 public:
  Block(World *world);

 private:
  Block();
};
}  // namespace GameBall::Logic
