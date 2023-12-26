#include "GameX/animation/entity.h"

#include "GameX/animation/manager.h"

namespace GameX::Animation {
Entity::~Entity() {
}

void Entity::Update(float delta_time) {
  accumulated_time_ += delta_time;
  glm::vec3 x = x_ + v_ * accumulated_time_ +
                0.5f * a_ * accumulated_time_ * accumulated_time_;
  glm::vec3 omega = R_ * I_inv_ * ((L_ + accumulated_time_ * tau_) * R_);
  float theta = glm::length(omega);
  glm::mat4 R{1.0f};
  if (theta > 0.0f) {
    R = glm::rotate(glm::mat4{1.0f}, theta * delta_time, omega);
  }
  R_ = glm::mat3{R} * R_;
  EntitySettings settings;
  auto R_final = glm::mat4{R_};
  R_final[3][3] = 1.0f;
  settings.model = glm::translate(glm::mat4{1.0f}, x) * R_final * affine_;
  //        R_final = R_final;
  //        printf("accumulated_time: %f\n", delta_time);
  //        printf("%f %f %f %f\n", R_final[0][0], R_final[0][1], R_final[0][2],
  //        R_final[0][3]); printf("%f %f %f %f\n", R_final[1][0],
  //        R_final[1][1], R_final[1][2], R_final[1][3]); printf("%f %f %f
  //        %f\n", R_final[2][0], R_final[2][1], R_final[2][2], R_final[2][3]);
  //        printf("%f %f %f %f\n", R_final[3][0], R_final[3][1], R_final[3][2],
  //        R_final[3][3]); spdlog::info("Entity position: ({}, {}, {})", x.x,
  //        x.y, x.z); spdlog::info("Entity scale: ({}, {}, {})", affine_[0][0],
  //        affine_[1][1], affine_[2][2]);
  entity_->SetEntitySettings(settings);
}

Entity::Entity(struct Scene *scene, Model *model)
    : DynamicObject(scene->Manager()) {
  manager_->RecordCommand([this, scene, model]() {
    entity_ = scene->Handle()->CreateEntity(model->Handle());
  });
}

void Entity::SetMotion(glm::vec3 x,
                       glm::vec3 v,
                       glm::vec3 a,
                       glm::mat3 R,
                       glm::vec3 axis,
                       float omega) {
  axis = glm::normalize(axis);
  SetMotion(x, v, a, R, axis * omega, glm::vec3{0.0f}, glm::mat3{1.0f});
}

void Entity::SetMotion(glm::vec3 x,
                       glm::vec3 v,
                       glm::vec3 a,
                       glm::mat3 R,
                       glm::vec3 L,
                       glm::vec3 tau,
                       glm::mat3 I) {
  manager_->RecordCommand([this, x, v, a, R, L, tau, I]() {
    x_ = x;
    v_ = v;
    a_ = a;
    R_ = R;
    L_ = L;
    tau_ = tau;
    I_ = I;
    I_inv_ = glm::inverse(I_);
    accumulated_time_ = 0.0f;
  });
}

void Entity::SetScale(glm::vec3 scale) {
  SetAffine(glm::scale(glm::mat4{1.0f}, scale));
}

void Entity::SetAffine(glm::mat4 affine) {
  manager_->RecordCommand([this, affine]() { affine_ = affine; });
}
}  // namespace GameX::Animation
