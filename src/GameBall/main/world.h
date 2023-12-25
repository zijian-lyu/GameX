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
  GameX::Animation::Entity *static_entity_;
  GameX::Animation::Entity *dynamic_entity_;
  GameX::Animation::AmbientLight *ambient_light_;
  GameX::Animation::DirectionalLight *directional_light_;
};
}  // namespace GameBall
