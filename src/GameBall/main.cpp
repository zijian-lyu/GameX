#include "GameBall/main/game_ball.h"

int main() {
  GameBall::GameSettings settings;
  GameBall::GameBall game(settings);
  game.Run();
  return 0;
}
