#pragma once

#include "GameX/utils/vertex.h"
#include "glm/gtc/matrix_transform.hpp"

namespace GameX::Base {
struct Mesh {
 public:
  Mesh() = default;

  Mesh(const std::vector<Vertex> &vertices,
       const std::vector<uint32_t> &indices);

  Mesh(const std::vector<glm::vec3> &positions,
       const std::vector<uint32_t> &indices,
       glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
       glm::vec2 texCoord = glm::vec2(0.0f, 0.0f),
       glm::vec3 normal = glm::vec3(0.0f, 0.0f, 0.0f),
       glm::vec3 tangent = glm::vec3(0.0f, 0.0f, 0.0f));

  Mesh(const std::string &path);

  std::vector<Vertex> &Vertices();

  const std::vector<Vertex> &Vertices() const;

  std::vector<uint32_t> &Indices();

  const std::vector<uint32_t> &Indices() const;

 private:
  std::vector<Vertex> vertices_{};
  std::vector<uint32_t> indices_{};
};
}  // namespace GameX::Base
