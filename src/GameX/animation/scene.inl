#pragma once
#include "GameX/animation/manager.h"
#include "GameX/animation/scene.h"

namespace GameX::Animation {
template <class... Args>
Scene::Scene(class Manager *manager, Args &&...args) : Object(manager) {
  manager_->RecordCommand([this, args...]() {
    scene_ = std::make_unique<GameX::Base::Scene>(manager_->Renderer(), args...);
  });
}
}  // namespace GameX::Animation
