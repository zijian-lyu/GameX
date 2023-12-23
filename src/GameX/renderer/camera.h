#pragma once
#include "GameX/utils/utils.h"

namespace GameX {
class Scene;
class Camera {
 public:
  Camera() = default;
  Camera(Scene *scene,
         const glm::vec3 eye = {},
         const glm::vec3 center = {},
         const float fovY = 45.0f,
         const float aspect = 1.0f,
         const float near_z = 0.1f,
         const float far_z = 100.0f);

  ~Camera();

  void Init(Scene *scene,
            const glm::vec3 eye = {},
            const glm::vec3 center = {},
            const float fovY = 45.0f,
            const float aspect = 1.0f,
            const float near_z = 0.1f,
            const float far_z = 100.0f);

  struct CameraData {
    glm::mat4 view_matrix_;
    glm::mat4 projection_matrix_;
  };

 private:
  Scene *scene_;
  std::unique_ptr<grassland::vulkan::DynamicBuffer<CameraData>> camera_buffer_;
  std::vector<std::unique_ptr<grassland::vulkan::DescriptorSet>>
      descriptor_sets_;
};

}  // namespace GameX
