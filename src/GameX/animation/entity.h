#pragma once
#include "GameX/animation/dynamic_object.h"
#include "GameX/animation/model.h"
#include "GameX/renderer/entity.h"

namespace GameX::Animation {
class Entity : public DynamicObject {
 public:
  typedef Base::Entity::EntitySettings EntitySettings;
  Entity(class Scene *scene, Model *model);
  virtual ~Entity();
  void Update(float delta_time) override;
  void SetMotion(glm::vec3 x,
                 glm::vec3 v = glm::vec3{0.0f},
                 glm::vec3 a = glm::vec3{0.0f},
                 glm::mat3 R = glm::mat3{1.0f},
                 glm::vec3 axis = glm::vec3{0.0f},
                 float omega = 0.0f);
  void SetMotion(glm::vec3 x,
                 glm::vec3 v,
                 glm::vec3 a,
                 glm::mat3 R,
                 glm::vec3 L,
                 glm::vec3 tau,
                 glm::mat3 I);
  void SetScale(glm::vec3 scale);
  void SetAffine(glm::mat4 affine);

 private:
  std::unique_ptr<Base::Entity> entity_;
  glm::mat4 affine_{1.0f};  // scale
  glm::vec3 x_{};           // position
  glm::vec3 v_{};           // velocity
  glm::vec3 a_{};           // acceleration
  glm::mat3 R_{1.0f};       // rotation matrix
  glm::vec3 L_{};           // angular momentum
  glm::vec3 tau_{};         // torque
  glm::mat3 I_{1.0f};       // inertia tensor
  glm::mat3 I_inv_{1.0f};   // inverse of inertia tensor
  float accumulated_time_{0.0f};
};
}  // namespace GameX::Animation
