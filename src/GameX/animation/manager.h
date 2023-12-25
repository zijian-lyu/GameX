#pragma once
#include <queue>

#include "GameX/renderer/renderer.h"

namespace GameX::Animation {
class Manager {
 public:
  Manager(Base::Renderer *renderer);
  ~Manager();

  void Update(float delta_time);

 private:
  Base::Renderer *renderer_;
  std::unique_ptr<Base::Scene> scene_;
  std::unique_ptr<Base::RenderPipeline::Film> film_;
};
}  // namespace GameX::Animation
