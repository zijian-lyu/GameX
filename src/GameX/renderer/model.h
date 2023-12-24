#pragma once
#include "GameX/utils/mesh.h"
#include "GameX/utils/utils.h"

namespace GameX {
class Renderer;
struct Model {
 public:
  Model(Renderer *renderer);

  virtual grassland::vulkan::Buffer *VertexBuffer(int frame_index) const = 0;

  virtual grassland::vulkan::Buffer *IndexBuffer(int frame_index) const = 0;

  virtual uint32_t IndexCount() const = 0;

 protected:
  Renderer *renderer_;
};

struct StaticModel : public Model {
 public:
  StaticModel(Renderer *renderer, const Mesh &mesh);

  grassland::vulkan::Buffer *VertexBuffer(int frame_index) const override {
    return vertex_buffer_.GetBuffer(frame_index);
  }

  grassland::vulkan::Buffer *IndexBuffer(int frame_index) const override {
    return index_buffer_.GetBuffer(frame_index);
  }

  uint32_t IndexCount() const override {
    return index_buffer_.Length();
  }

 private:
  grassland::vulkan::StaticBuffer<Vertex> vertex_buffer_;
  grassland::vulkan::StaticBuffer<uint32_t> index_buffer_;
};

struct DynamicModel : public Model {
 public:
  DynamicModel(Renderer *renderer, const Mesh *mesh);
  ~DynamicModel();
  bool SyncData(VkCommandBuffer cmd_buffer);
  bool SyncData(std::function<void(VkCommandBuffer)> &func);
  bool SyncData(VkCommandBuffer cmd_buffer, uint32_t frame_index);
  bool SyncData(std::function<void(VkCommandBuffer)> &func,
                uint32_t frame_index);

  grassland::vulkan::Buffer *VertexBuffer(int frame_index) const override {
    return vertex_buffer_.GetBuffer(frame_index);
  }

  grassland::vulkan::Buffer *IndexBuffer(int frame_index) const override {
    return index_buffer_.GetBuffer(frame_index);
  }

  uint32_t IndexCount() const override {
    return mesh_->Indices().size();
  }

  void SyncMeshData();

 private:
  grassland::vulkan::DynamicBuffer<Vertex> vertex_buffer_;
  grassland::vulkan::StaticBuffer<uint32_t> index_buffer_;
  const Mesh *mesh_;
};
}  // namespace GameX
