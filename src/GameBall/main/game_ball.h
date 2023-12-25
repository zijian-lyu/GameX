#pragma once
#include "GameBall/utils/utils.h"

namespace GameBall {

struct GameSettings {
  bool fullscreen{false};
  int width{-1};
  int height{-1};
  GameX::Base::ApplicationSettings GetApplicationSettings() const {
    return {fullscreen, width, height};
  }
};

class GameBall : public GameX::Base::Application {
 public:
  GameBall(const GameSettings &settings);
  ~GameBall();

  void OnInit() override;

 private:
};
}  // namespace GameBall
