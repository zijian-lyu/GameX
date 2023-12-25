#pragma once

#include "GameX/utils/common.h"

namespace GameX::Base {
struct Vertex {
  glm::vec3 position{};
  glm::vec3 color{};
  glm::vec2 texCoord{};
  glm::vec3 normal{};
  glm::vec3 tangent{};

  static VkVertexInputBindingDescription GetBindingDescription() {
    VkVertexInputBindingDescription binding_description{};
    binding_description.binding = 0;
    binding_description.stride = sizeof(Vertex);
    binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return binding_description;
  }

  static std::array<VkVertexInputAttributeDescription, 5>
  GetAttributeDescriptions() {
    std::array<VkVertexInputAttributeDescription, 5> attribute_descriptions{};

    attribute_descriptions[0].binding = 0;
    attribute_descriptions[0].location = 0;
    attribute_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attribute_descriptions[0].offset = offsetof(Vertex, position);

    attribute_descriptions[1].binding = 0;
    attribute_descriptions[1].location = 1;
    attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attribute_descriptions[1].offset = offsetof(Vertex, color);

    attribute_descriptions[2].binding = 0;
    attribute_descriptions[2].location = 2;
    attribute_descriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
    attribute_descriptions[2].offset = offsetof(Vertex, texCoord);

    attribute_descriptions[3].binding = 0;
    attribute_descriptions[3].location = 3;
    attribute_descriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
    attribute_descriptions[3].offset = offsetof(Vertex, normal);

    attribute_descriptions[4].binding = 0;
    attribute_descriptions[4].location = 4;
    attribute_descriptions[4].format = VK_FORMAT_R32G32B32_SFLOAT;
    attribute_descriptions[4].offset = offsetof(Vertex, tangent);

    return attribute_descriptions;
  }

  bool operator<(const Vertex &other) const {
    if (position.x < other.position.x) {
      return true;
    } else if (position.x > other.position.x) {
      return false;
    } else if (position.y < other.position.y) {
      return true;
    } else if (position.y > other.position.y) {
      return false;
    } else if (position.z < other.position.z) {
      return true;
    } else if (position.z > other.position.z) {
      return false;
    } else if (normal.x < other.normal.x) {
      return true;
    } else if (normal.x > other.normal.x) {
      return false;
    } else if (normal.y < other.normal.y) {
      return true;
    } else if (normal.y > other.normal.y) {
      return false;
    } else if (normal.z < other.normal.z) {
      return true;
    } else if (normal.z > other.normal.z) {
      return false;
    } else if (texCoord.x < other.texCoord.x) {
      return true;
    } else if (texCoord.x > other.texCoord.x) {
      return false;
    } else if (texCoord.y < other.texCoord.y) {
      return true;
    } else if (texCoord.y > other.texCoord.y) {
      return false;
    } else if (tangent.x < other.tangent.x) {
      return true;
    } else if (tangent.x > other.tangent.x) {
      return false;
    } else if (tangent.y < other.tangent.y) {
      return true;
    } else if (tangent.y > other.tangent.y) {
      return false;
    } else if (tangent.z < other.tangent.z) {
      return true;
    } else if (tangent.z > other.tangent.z) {
      return false;
    } else if (color.x < other.color.x) {
      return true;
    } else if (color.x > other.color.x) {
      return false;
    } else if (color.y < other.color.y) {
      return true;
    } else if (color.y > other.color.y) {
      return false;
    } else if (color.z < other.color.z) {
      return true;
    } else if (color.z > other.color.z) {
      return false;
    } else {
      return false;
    }
  }
};
}  // namespace GameX::Base
