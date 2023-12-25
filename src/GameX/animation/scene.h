#pragma once
#include "GameX/animation/object.h"

namespace GameX::Animation {
class Scene : public Object {
 public:
  template <class... Args>
  Scene(class Manager *manager, Args &&...args);

  ~Scene() override;

 private:
  std::unique_ptr<GameX::Base::Scene> scene_;
};
}  // namespace GameX::Animation
