#pragma once
#include "GameBall/core/utils.h"

namespace GameBall {
class GameBall;
class Actor {
 public:
  Actor(GameBall *app);
  ~Actor();
  uint64_t SyncedLogicWorldVersion() const;

 protected:
  GameBall *app_;
  uint64_t synced_logic_world_version_{0};
};
}  // namespace GameBall
