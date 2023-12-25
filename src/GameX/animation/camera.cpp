#include "GameX/animation/camera.h"

#include "GameX/animation/manager.h"

namespace GameX::Animation {
void Camera::Update(float delta_time) {
}

// Camera::Camera(class Scene *scene,
//                const glm::vec3 eye,
//                const glm::vec3 center,
//                const float fovY,
//                const float aspect,
//                const float near_z,
//                const float far_z): DynamicObject(scene->Manager()) {
//   manager_->RecordCommand(
//         [this, scene, eye, center, fovY, aspect, near_z, far_z]() {
//           camera_ = std::make_unique<Base::Camera>(
//                 scene->Handle(),
//                 eye,
//                 center,
//                 fovY,
//                 aspect,
//                 near_z,
//                 far_z);
//         }
//       );
// }
}  // namespace GameX::Animation
