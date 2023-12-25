#pragma once
#include "GameX/animation/dynamic_object.h"
#include "GameX/renderer/camera.h"

namespace GameX::Animation {
class Camera : public DynamicObject {
 public:
  template <class... Args>
  Camera(class Scene *scene, Args &&...args);

  void Update(float delta_time) override;

  Base::Camera *Handle() const {
    return camera_.get();
  }

 private:
  std::unique_ptr<Base::Camera> camera_;
};
}  // namespace GameX::Animation
