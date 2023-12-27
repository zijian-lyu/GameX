#pragma once
#include "GameBall/logic/object.h"

namespace GameBall::Logic {
class Unit : public Object {
 public:
  Unit(World *world);
  virtual ~Unit();
  uint64_t UnitId() const;

 private:
  uint64_t unit_id_;
};
}  // namespace GameBall::Logic
