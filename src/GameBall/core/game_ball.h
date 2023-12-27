#pragma once
#include "GameBall/core/utils.h"

namespace GameBall {

typedef GameX::Base::ApplicationSettings GameSettings;

class GameBall : public GameX::Base::Application {
 public:
  GameBall(const GameSettings &settings);
  ~GameBall();

  void OnInit() override;

  void OnUpdate() override;

  void OnRender() override;

  void OnCleanup() override;

 private:
  GameX::Graphics::UScene scene_;
  GameX::Graphics::UFilm film_;
  GameX::Graphics::UStaticModel static_model_;
  GameX::Graphics::UAnimatedModel animated_model_;
  GameX::Graphics::UEntity static_entity_;
  GameX::Graphics::UEntity animated_entity_;
  GameX::Graphics::UCamera camera_;
  GameX::Graphics::UImage moon_texture_;
  GameX::Graphics::UImage envmap_texture_;
  GameX::Graphics::UAmbientLight ambient_light_;
  GameX::Graphics::UDirectionalLight directional_light_;
};
}  // namespace GameBall
