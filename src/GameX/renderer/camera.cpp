#include "GameX/renderer/camera.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"
#include "glm/gtc/matrix_transform.hpp"

namespace GameX {

Camera::Camera(Scene *scene,
               const glm::vec3 eye,
               const glm::vec3 center,
               const float fovY,
               const float aspect,
               const float near_z,
               const float far_z) {
  Init(scene, eye, center, fovY, aspect, near_z, far_z);
}

void Camera::Init(Scene *scene,
                  const glm::vec3 eye,
                  const glm::vec3 center,
                  const float fovY,
                  const float aspect,
                  const float near_z,
                  const float far_z) {
  camera_buffer_ =
      std::make_unique<grassland::vulkan::DynamicBuffer<CameraData>>(
          scene->Renderer()->App()->Core(), 1,
          VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);

  camera_buffer_->At(0).view_matrix_ = glm::lookAt(eye, center, {0, 1, 0});
  camera_buffer_->At(0).projection_matrix_ =
      glm::perspective(glm::radians(fovY), aspect, near_z, far_z);
}

}  // namespace GameX
