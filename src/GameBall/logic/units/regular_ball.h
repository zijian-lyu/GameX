#pragma once
#include "GameBall/logic/unit.h"

namespace GameBall::Logic::Units {
class RegularBall : public Unit {
 public:
  RegularBall(World *world);
  ~RegularBall();

 private:
};
}  // namespace GameBall::Logic::Units
