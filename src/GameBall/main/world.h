#pragma once
#include "GameBall/main/game_ball.h"

namespace GameBall {
class World : public GameX::Base::Module {
 public:
  World(GameX::Base::Core *core);
  ~World();
  void Update() override;

 private:
};
}  // namespace GameBall
