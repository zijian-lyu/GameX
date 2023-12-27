#include "GameBall/core/actors/common_ball_actor.h"

#include "GameBall/core/game_ball.h"

namespace GameBall {

CommonBallActor::CommonBallActor(GameBall *app) : Actor(app) {
  entity_ = app->Scene()->CreateEntity(
      app->AssetManager()->StaticModelFile("models/sphere.obj"));
}

CommonBallActor::~CommonBallActor() {
}
}  // namespace GameBall
