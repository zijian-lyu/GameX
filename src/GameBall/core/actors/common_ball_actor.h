#pragma once
#include "GameBall/core/actor.h"

namespace GameBall::Actors {
class CommonBallActor : public Actor {
 public:
  CommonBallActor(GameBall *app);
  ~CommonBallActor();

  void Update(float delta_time) override;

  void SetMomentOfInertia(float moment_of_inertia);

  void SetInertiaTensor(const glm::mat3 &inertia_tensor);

  void SetWeight(float weight);

  void SetGravity(const glm::vec3 &gravity);

  void SetTransform(const glm::mat3 &transform);

  void SetMotion(const glm::vec3 &position,
                 const glm::vec3 &velocity,
                 const glm::mat3 &rotation,
                 const glm::vec3 &angular_momentum);

  GameX::Graphics::PEntity Entity() const {
    return entity_.get();
  }

 private:
  GameX::Graphics::UEntity entity_;
  glm::mat3 transform_{1.0f};
  glm::vec3 velocity_{};

  glm::vec3 L_{0.0f};  // angular momentum
  glm::mat3 J_{1.0f};  // inertia tensor
  glm::mat3 J_inv_{1.0f};

  glm::vec3 gravity_{};
  float weight_{};
};
}  // namespace GameBall::Actors
