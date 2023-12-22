#pragma once
#include "GameX/utils/mesh.h"
#include "GameX/utils/utils.h"

namespace GameX {
class Renderer;
struct Object {
 public:
  Object(Renderer *renderer);

 protected:
  Renderer *renderer_;
};

struct StaticObject : public Object {
 public:
  StaticObject(Renderer *renderer, const Mesh &mesh);

 private:
  grassland::vulkan::StaticBuffer<Vertex> vertex_buffer_;
  grassland::vulkan::StaticBuffer<uint32_t> index_buffer_;
};

struct DynamicObject : public Object {
 public:
  DynamicObject(Renderer *renderer, const Mesh *mesh);
  ~DynamicObject();
  bool SyncData(VkCommandBuffer cmd_buffer);
  bool SyncData(std::function<void(VkCommandBuffer)> &func);
  bool SyncData(VkCommandBuffer cmd_buffer, uint32_t frame_index);
  bool SyncData(std::function<void(VkCommandBuffer)> &func,
                uint32_t frame_index);

 private:
  grassland::vulkan::DynamicBuffer<Vertex> vertex_buffer_;
  grassland::vulkan::StaticBuffer<uint32_t> index_buffer_;
  const Mesh *mesh_;
};
}  // namespace GameX
