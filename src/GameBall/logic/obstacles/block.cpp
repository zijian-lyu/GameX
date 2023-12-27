#include "GameBall/logic/obstacles/block.h"

#include "GameBall/core/game_ball.h"
#include "GameBall/logic/world.h"

namespace GameBall::Logic::Obstacles {
Block::Block(World *world,
             const glm::mat4 &transform,
             float weight,
             bool gravity)
    : Block(world,
            glm::vec3(transform[3]),
            weight,
            gravity,
            glm::mat3(transform)) {
}

Block::Block(World *world,
             glm::vec3 position,
             float weight,
             bool gravity,
             glm::vec3 scale)
    : Block(world,
            position,
            weight,
            gravity,
            glm::mat3{scale.x, 0.0f, 0.0f, 0.0f, scale.y, 0.0f, 0.0f, 0.0f,
                      scale.z}) {
}

Block::Block(World *world,
             glm::vec3 position,
             float weight,
             bool gravity,
             const glm::mat3 &transform)
    : Obstacle(world),
      position_(position),
      transform_(transform),
      gravity_(gravity ? glm::vec3{0.0f, -9.8f, 0.0f} : glm::vec3{0.0}),
      weight_(weight) {
}

SYNC_ACTOR_FUNC(Block) {
  actor->SetTransform(transform_);
  actor->SetWeight(weight_);
  actor->SetInertiaTensor(J_);
  actor->SetGravity(gravity_);
  actor->SetMotion(position_, velocity_, rotation_, L_);
}

void Block::SetMomentOfInertia(float moment_of_inertia) {
  J_ = glm::mat3{moment_of_inertia};
}

void Block::SetInertiaTensor(const glm::mat3 &inertia_tensor) {
  J_ = inertia_tensor;
}

void Block::SetWeight(float weight) {
  weight_ = weight;
}

void Block::SetGravity(const glm::vec3 &gravity) {
  gravity_ = gravity;
}

void Block::SetTransform(const glm::mat3 &transform) {
  transform_ = transform;
}

void Block::SetMotion(const glm::vec3 &position,
                      const glm::vec3 &velocity,
                      const glm::mat3 &rotation,
                      const glm::vec3 &angular_momentum) {
  rotation_ = rotation;
  position_ = position;
  velocity_ = velocity;
  L_ = angular_momentum;
}
}  // namespace GameBall::Logic::Obstacles
