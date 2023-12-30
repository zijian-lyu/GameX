#include "GameX/physics/cube.h"

namespace GameX::Physics {
Cube::Cube(float mass, float side_length) {
  SetSideLengthMass(side_length, mass);
}

Cube::~Cube() {
}

void Cube::SetSideLengthMass(float side_length, float mass) {
  this->side_length = side_length;
  this->mass = mass;
  if (std::isinf(mass)) {
    inertia = glm::mat3{mass};
    inertia_inv = glm::mat3{0.0f};
  } else {
    inertia = glm::mat3{mass * side_length * side_length / 6.0f};
    inertia_inv = glm::inverse(inertia);
  }
}

}  // namespace GameX::Physics
