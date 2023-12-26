#pragma once

#include "GameX/utils/mesh.h"
#include "GameX/utils/utils.h"

namespace GameX::Graphics {

typedef Base::Vertex Vertex;
typedef Base::Mesh Mesh;

class Renderer;

GAMEX_CLASS(Model) {
 public:
  Model(Renderer * renderer);

  virtual grassland::vulkan::Buffer *VertexBuffer(int frame_index) const = 0;

  virtual grassland::vulkan::Buffer *IndexBuffer(int frame_index) const = 0;

  virtual uint32_t IndexCount() const = 0;

 protected:
  Renderer *renderer_;
};

GAMEX_CLASS(StaticModel) : public Model {
 public:
  StaticModel(Renderer * renderer, const Base::Mesh &mesh);

  StaticModel(Renderer * renderer, const std::string &path);

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
  grassland::vulkan::StaticBuffer<Base::Vertex> vertex_buffer_;
  grassland::vulkan::StaticBuffer<uint32_t> index_buffer_;
};

GAMEX_CLASS(AnimatedModel) : public Model {
 public:
  AnimatedModel(Renderer * renderer, Base::Mesh * mesh);

  template <class... Args>
  AnimatedModel(Renderer * renderer, Args && ...args);

  ~AnimatedModel();

  void SyncMeshData();

  std::vector<Vertex> &Vertices() {
    return mesh_->Vertices();
  }

  std::vector<uint32_t> &Indices() {
    return mesh_->Indices();
  }

  const std::vector<Vertex> &Vertices() const {
    return mesh_->Vertices();
  }

  const std::vector<uint32_t> &Indices() const {
    return mesh_->Indices();
  }

 private:
  bool SyncData(VkCommandBuffer cmd_buffer);

  bool SyncData(std::function<void(VkCommandBuffer)> & func);

  bool SyncData(VkCommandBuffer cmd_buffer, uint32_t frame_index);

  bool SyncData(std::function<void(VkCommandBuffer)> & func,
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

  grassland::vulkan::DynamicBuffer<Base::Vertex> vertex_buffer_;
  grassland::vulkan::StaticBuffer<uint32_t> index_buffer_;
  Base::Mesh *mesh_{};
  bool is_referenced_{false};
};

}  // namespace GameX::Graphics
