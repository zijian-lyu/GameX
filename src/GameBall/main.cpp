#include "GameBall/core/game_ball.h"

int main() {
  GameBall::GameSettings settings;
  GameBall::GameBall game(settings);
  game.Run();
  return 0;
}
