#pragma once
#include "GameX/animation/lights/ambient_light.h"

#include "GameX/animation/scene.h"

namespace GameX::Animation {
template <class ...Args>
AmbientLight::AmbientLight(Scene* scene, Args&& ...args) : DynamicObject(scene->Manager()) {
  manager_->RecordCommand(
      [this, scene, args...]() {
        light_ = scene->Handle()->CreateLight<Base::AmbientLight>(args...);
      }
  );
}
}
