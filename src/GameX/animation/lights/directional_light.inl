#pragma once
#include "GameX/animation/lights/directional_light.h"
#include "GameX/animation/scene.h"

namespace GameX::Animation {
template <class... Args>
DirectionalLight::DirectionalLight(Scene *scene, Args &&...args)
    : DynamicObject(scene->Manager()) {
  manager_->RecordCommand([this, scene, args...]() {
    light_ = scene->Handle()->CreateLight<Base::DirectionalLight>(args...);
  });
}
}  // namespace GameX::Animation
