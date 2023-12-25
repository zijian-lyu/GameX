#pragma once
#include "GameBall/main/game_ball.h"

namespace GameBall {
class World : public GameX::Base::Module {
 public:
  World(GameX::Base::Core *core);
  ~World();
  void Update() override;

 private:
  GameX::Animation::Scene *scene_;
  GameX::Animation::Camera *camera_;
  GameX::Animation::Mesh *cube_;
  GameX::Animation::StaticModel *static_model_;
  GameX::Animation::DynamicModel *dynamic_model_;
};
}  // namespace GameBall
