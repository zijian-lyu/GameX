#pragma once
#include "GameX/physics/rigid_body.h"
#include "GameX/utils/utils.h"

namespace GameX::Physics {
struct Cube : public RigidBody {
  Cube(float side_length = 1.0f, float mass = 1.0f);
  ~Cube();

  void SetSideLengthMass(float side_length = 1.0f, float mass = 1.0f);

  float side_length{1.0f};
};
}  // namespace GameX::Physics
