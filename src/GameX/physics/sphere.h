#pragma once
#include "GameX/physics/rigid_body.h"
#include "GameX/utils/utils.h"

namespace GameX::Physics {
struct Sphere : public RigidBody {
  Sphere(float radius = 1.0f, float mass = 1.0f);
  ~Sphere();

  void SetRadiusMass(float radius = 1.0f, float mass = 1.0f);

  float radius{1.0f};
};
}  // namespace GameX::Physics
