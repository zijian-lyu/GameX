#include "GameBall/main/game_ball.h"

#include "GameBall/main/world.h"

namespace GameBall {

GameBall::GameBall(const GameSettings &settings)
    : GameX::Base::Application(settings.GetApplicationSettings()) {
}

GameBall::~GameBall() {
}

void GameBall::OnInit() {
  GameCore()->LoadModule<World>();
}
}  // namespace GameBall
