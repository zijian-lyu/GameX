#pragma once
#include "GameBall/utils/utils.h"

namespace GameBall {

typedef GameX::Base::ApplicationSettings GameSettings;

class GameBall : public GameX::Base::Application {
 public:
  GameBall(const GameSettings &settings);
  ~GameBall();

  void OnInit() override;

 private:
};
}  // namespace GameBall
