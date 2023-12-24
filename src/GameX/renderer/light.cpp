#include "GameX/renderer/light.h"

#include "GameX/renderer/scene.h"

namespace GameX {
Light::~Light() {
  scene_->DestroyLight(this);
}
}  // namespace GameX
