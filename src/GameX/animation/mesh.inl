#pragma once
#include "GameX/animation/manager.h"
#include "GameX/animation/mesh.h"

namespace GameX::Animation {
template <class... Args>
Mesh::Mesh(class Manager *manager, Args &&...args) : Object(manager) {
  mesh_ = Base::Mesh(std::forward<Args...>(args...));
  reference_mesh_ = mesh_;
}
}  // namespace GameX::Animation
