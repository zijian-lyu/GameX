#pragma once
#include "GameX/animation/dynamic_object.h"
#include "GameX/renderer/lights/ambient_light.h"

namespace GameX::Animation {
class AmbientLight : public DynamicObject {
 public:
  typedef Base::AmbientLight::AmbientLightData AmbientLightData;

  template <class... Args>
  AmbientLight(class Scene *scene, Args &&...args);

  virtual ~AmbientLight();
  void Update(float delta_time) override;

 private:
  std::unique_ptr<Base::AmbientLight> light_;
};
}  // namespace GameX::Animation
