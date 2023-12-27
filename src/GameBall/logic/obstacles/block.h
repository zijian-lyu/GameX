#pragma once

#include "GameBall/logic/obstacle.h"

namespace GameBall::Logic::Obstacles {
class Block : public Obstacle {
 public:
  Block(World *world,
        glm::vec3 position,
        float weight = std::numeric_limits<float>::infinity(),
        bool gravity = false,
        const glm::mat3 &transform = glm::mat3(1.0f));

  Block(World *world,
        glm::vec3 position,
        float weight = std::numeric_limits<float>::infinity(),
        bool gravity = false,
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));

  Block(World *world,
        const glm::mat4 &transform,
        float weight = std::numeric_limits<float>::infinity(),
        bool gravity = false);

  SYNC_ACTOR_FUNC_DECLARE(Actors::CommonBlockActor)

  void SetMomentOfInertia(float moment_of_inertia);

  void SetInertiaTensor(const glm::mat3 &inertia_tensor);

  void SetWeight(float weight);

  void SetGravity(const glm::vec3 &gravity);

  void SetTransform(const glm::mat3 &transform);

  void SetMotion(const glm::vec3 &position,
                 const glm::vec3 &velocity,
                 const glm::mat3 &rotation,
                 const glm::vec3 &angular_momentum);

  void UpdateTick() override;

 private:
  glm::mat3 transform_{};
  glm::vec3 position_{};
  glm::vec3 velocity_{};

  glm::mat3 rotation_{1.0f};
  glm::vec3 L_{0.0f};  // angular momentum
  glm::mat3 J_{1.0f};  // inertia tensor

  glm::vec3 gravity_{};
  float weight_{};
};
}  // namespace GameBall::Logic::Obstacles
