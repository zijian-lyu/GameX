#include "GameBall/logic/obstacle.h"

#include "GameBall/logic/world.h"

namespace GameBall::Logic {
Obstacle::Obstacle(World *world) : Object(world) {
  obstacle_id_ = world_->RegisterObstacle(this);
}

Obstacle::~Obstacle() {
  world_->UnregisterObstacle(obstacle_id_);
}
}  // namespace GameBall::Logic
