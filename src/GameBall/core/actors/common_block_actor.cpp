#include "GameBall/core/actors/common_block_actor.h"

#include "GameBall/core/game_ball.h"

namespace GameBall::Actors {
CommonBlockActor::CommonBlockActor(GameBall *app) : Actor(app) {
  entity_ = app_->Scene()->CreateEntity(
      app_->AssetManager()->StaticModelFile("models/cube.obj"));
}

CommonBlockActor::~CommonBlockActor() {
}

void CommonBlockActor::Update(float delta_time) {
  glm::vec3 acceleration = gravity_;
  velocity_ += acceleration * delta_time;
  position_ += velocity_ * delta_time;

  glm::vec3 omega = rotation_ * J_inv_ * (L_ * rotation_);
  float theta = glm::length(omega) * delta_time;
  if (theta > 0.0f) {
    rotation_ =
        glm::mat3{glm::rotate(glm::mat4{1.0f}, theta, omega)} * rotation_;
  }

  entity_->SetAffineMatrix(glm::translate(glm::mat4{1.0f}, position_) *
                           glm::mat4{rotation_} * glm::mat4{transform_});
}

void CommonBlockActor::SetMomentOfInertia(float moment_of_inertia) {
  J_ = glm::mat3{moment_of_inertia};
  J_inv_ = glm::mat3{1.0f / moment_of_inertia};
}

void CommonBlockActor::SetInertiaTensor(const glm::mat3 &inertia_tensor) {
  J_ = inertia_tensor;
  J_inv_ = glm::inverse(inertia_tensor);
}

void CommonBlockActor::SetWeight(float weight) {
  weight_ = weight;
}

void CommonBlockActor::SetGravity(const glm::vec3 &gravity) {
  gravity_ = gravity;
}

void CommonBlockActor::SetTransform(const glm::mat3 &transform) {
  transform_ = transform;
}

void CommonBlockActor::SetMotion(const glm::vec3 &position,
                                 const glm::vec3 &velocity,
                                 const glm::mat3 &rotation,
                                 const glm::vec3 &angular_momentum) {
  rotation_ = rotation;
  position_ = position;
  velocity_ = velocity;
  L_ = angular_momentum;
}
}  // namespace GameBall::Actors
