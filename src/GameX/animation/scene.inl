#pragma once
#include "GameX/animation/scene.h"

namespace GameX::Animation {
template <class... Args>
Scene::Scene(Manager *manager, Args &&...args) : Object(manager) {
  scene_ = std::make_unique<GameX::Base::Scene>(manager_->Renderer(), std::forward<Args>(args)...);
}
}
