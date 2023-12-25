#pragma once
#include "GameX/animation/object.h"
#include "GameX/renderer/renderer.h"

namespace GameX::Animation {
class Mesh : public Object {
 public:
  template <class... Args>
  Mesh(class Manager *manager, Args &&...args);

  ~Mesh();

  std::vector<Base::Vertex> &Vertices();

  const std::vector<Base::Vertex> &Vertices() const;

  std::vector<uint32_t> &Indices();

  const std::vector<uint32_t> &Indices() const;

 private:
  Base::Mesh mesh_;
  Base::Mesh reference_mesh_;
};
}  // namespace GameX::Animation
