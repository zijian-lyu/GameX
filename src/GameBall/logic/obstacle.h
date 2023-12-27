#pragma once
#include "GameBall/logic/object.h"

namespace GameBall::Logic {
class Obstacle : public Object {
 public:
  Obstacle(World *world);
  ~Obstacle();

 private:
  uint64_t obstacle_id_;
};
}  // namespace GameBall::Logic
