#include "GameX/utils/mesh.h"

// Include assimp
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

namespace GameX::Base {
Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<uint32_t> &indices) {
  vertices_ = vertices;
  indices_ = indices;
}

Mesh::Mesh(const std::vector<glm::vec3> &positions,
           const std::vector<uint32_t> &indices,
           glm::vec3 color,
           glm::vec2 texCoord,
           glm::vec3 normal,
           glm::vec3 tangent) {
  vertices_.reserve(positions.size());
  for (const auto &position : positions) {
    vertices_.push_back({position, color, texCoord, normal, tangent});
  }
  indices_ = indices;
}

std::vector<Vertex> &Mesh::Vertices() {
  return vertices_;
}

const std::vector<Vertex> &Mesh::Vertices() const {
  return vertices_;
}

std::vector<uint32_t> &Mesh::Indices() {
  return indices_;
}

const std::vector<uint32_t> &Mesh::Indices() const {
  return indices_;
}

Mesh::Mesh(const std::string &path) {
  LAND_INFO("Loading model: {}", path);
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(
      path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs |
                aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    LAND_ERROR("Failed to load model: {}", path);
  }

  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;

  for (uint32_t i = 0; i < scene->mNumMeshes; ++i) {
    const aiMesh *mesh = scene->mMeshes[i];
    for (uint32_t j = 0; j < mesh->mNumVertices; ++j) {
      Vertex vertex;
      vertex.position = {mesh->mVertices[j].x, mesh->mVertices[j].y,
                         mesh->mVertices[j].z};
      vertex.color = {1.0f, 1.0f, 1.0f};
      if (mesh->mColors[0]) {
        vertex.color = {mesh->mColors[0][j].r, mesh->mColors[0][j].g,
                        mesh->mColors[0][j].b};
      }
      vertex.texCoord = {0.0f, 0.0f};
      if (mesh->mTextureCoords[0]) {
        vertex.texCoord = {mesh->mTextureCoords[0][j].x,
                           mesh->mTextureCoords[0][j].y};
      }
      vertex.normal = {mesh->mNormals[j].x, mesh->mNormals[j].y,
                       mesh->mNormals[j].z};
      vertex.tangent = {mesh->mTangents[j].x, mesh->mTangents[j].y,
                        mesh->mTangents[j].z};
      vertices.push_back(vertex);
    }

    for (uint32_t j = 0; j < mesh->mNumFaces; ++j) {
      const aiFace &face = mesh->mFaces[j];
      for (uint32_t k = 0; k < face.mNumIndices; ++k) {
        indices.push_back(face.mIndices[k]);
      }
    }
  }

  vertices_ = vertices;
  indices_ = indices;
}
}  // namespace GameX::Base
