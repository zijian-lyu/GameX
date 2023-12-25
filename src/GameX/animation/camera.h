#pragma once
#include "GameX/animation/dynamic_object.h"
#include "GameX/renderer/camera.h"

namespace GameX::Animation {
class Camera : public DynamicObject {
 public:
  //  Camera(class Scene *scene,
  //         const glm::vec3 eye = {},
  //         const glm::vec3 center = {},
  //         const float fovY = 45.0f,
  //         const float aspect = 1.0f,
  //         const float near_z = 0.1f,
  //         const float far_z = 100.0f);

  template <class... Args>
  Camera(class Scene *scene, Args &&...args);

  void Update(float delta_time) override;

 private:
  std::unique_ptr<Base::Camera> camera_;
};
}  // namespace GameX::Animation
