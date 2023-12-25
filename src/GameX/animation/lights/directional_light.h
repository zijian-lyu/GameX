#pragma once
#include "GameX/animation/dynamic_object.h"
#include "GameX/renderer/lights/directional_light.h"

namespace GameX::Animation {
class DirectionalLight : public DynamicObject {
 public:
  typedef Base::DirectionalLight::DirectionalLightData DirectionalLightData;

  template <class... Args>
  DirectionalLight(class Scene *scene, Args &&...args);

  virtual ~DirectionalLight();

  void Update(float delta_time) override;

 private:
  std::unique_ptr<Base::DirectionalLight> light_;
};
}  // namespace GameX::Animation
