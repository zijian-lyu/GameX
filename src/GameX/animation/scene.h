#pragma once
#include "GameX/animation/camera.h"
#include "GameX/animation/object.h"

namespace GameX::Animation {
class Scene : public Object {
 public:
  template <class... Args>
  Scene(class Manager *manager, Args &&...args);

  ~Scene() override;

  template <class... Args>
  [[nodiscard]] Camera *CreateCamera(Args &&...args) {
    return new Camera(this, std::forward<Args>(args)...);
  }

  GameX::Base::Scene *Handle() const {
    return scene_.get();
  }

 private:
  std::unique_ptr<GameX::Base::Scene> scene_;
};
}  // namespace GameX::Animation
