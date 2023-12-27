#pragma once
#include "GameBall/core/utils.h"

namespace GameBall {

namespace Logic {
class World;
}

class GameBall;
class Actor {
 public:
  Actor(GameBall *app);
  virtual ~Actor();
  uint64_t SyncedLogicWorldVersion() const;

  virtual void Update(float delta_time){};

 protected:
  friend class Logic::World;
  GameBall *app_;
  uint64_t synced_logic_world_version_{0};
};
}  // namespace GameBall
