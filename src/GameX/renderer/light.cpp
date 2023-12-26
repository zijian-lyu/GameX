#include "GameX/renderer/light.h"

#include "GameX/renderer/scene.h"

namespace GameX::Graphics {
Light::~Light() {
  scene_->DestroyLight(this);
}
}  // namespace GameX::Graphics
