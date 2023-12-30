#include "GameX/physics/sphere.h"

namespace GameX::Physics {

Sphere::Sphere(float radius, float mass) {
  SetRadiusMass(radius, mass);
}

Sphere::~Sphere() {
}

void Sphere::SetRadiusMass(float radius, float mass) {
  this->radius = radius;
  this->mass = mass;
  inertia = glm::mat3{0.4f * mass * radius * radius};
  inertia_inv = glm::inverse(inertia);
}

}  // namespace GameX::Physics
