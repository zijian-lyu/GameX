#include "GameBall/core/actors/common_ball_actor.h"

#include "GameBall/core/game_ball.h"

namespace GameBall::Actors {

CommonBallActor::CommonBallActor(GameBall *app) : Actor(app) {
  entity_ = app->Scene()->CreateEntity(
      app->AssetManager()->StaticModelFile("models/sphere.obj"));
  entity_->SetAlbedoImage(
      app->AssetManager()->ImageFile("textures/2k_moon.jpg"));
}

CommonBallActor::~CommonBallActor() {
}

void CommonBallActor::Update(float delta_time) {
}

}  // namespace GameBall::Actors
