#include "GameX/renderer/model.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"

namespace GameX::Graphics {

Model::Model(Renderer *renderer) : renderer_(renderer) {
}

StaticModel::StaticModel(Renderer *renderer, const Base::Mesh &mesh)
    : Model(renderer) {
  vertex_buffer_.Init(renderer_->App()->VkCore(), mesh.Vertices().size());
  vertex_buffer_.UploadContents(mesh.Vertices().data(), mesh.Vertices().size());
  index_buffer_.Init(renderer_->App()->VkCore(), mesh.Indices().size());
  index_buffer_.UploadContents(mesh.Indices().data(), mesh.Indices().size());
}

DynamicModel::DynamicModel(Renderer *renderer, const Base::Mesh *mesh)
    : Model(renderer), mesh_(mesh) {
  vertex_buffer_.Init(renderer_->App()->VkCore(), mesh->Vertices().size());
  vertex_buffer_.UploadContents(mesh->Vertices().data(),
                                mesh->Vertices().size());
  index_buffer_.Init(renderer_->App()->VkCore(), mesh->Indices().size());
  index_buffer_.UploadContents(mesh->Indices().data(), mesh->Indices().size());

  renderer_->RegisterSyncObject(&vertex_buffer_);
}

DynamicModel::~DynamicModel() {
  renderer_->UnregisterSyncObject(&vertex_buffer_);
}

bool DynamicModel::SyncData(VkCommandBuffer cmd_buffer) {
  ;
  return SyncData(cmd_buffer, renderer_->App()->VkCore()->CurrentFrame());
}

bool DynamicModel::SyncData(std::function<void(VkCommandBuffer)> &func) {
  return SyncData(func, renderer_->App()->VkCore()->CurrentFrame());
}

bool DynamicModel::SyncData(VkCommandBuffer cmd_buffer, uint32_t frame_index) {
  return vertex_buffer_.SyncData(cmd_buffer, frame_index);
}

bool DynamicModel::SyncData(std::function<void(VkCommandBuffer)> &func,
                            uint32_t frame_index) {
  return vertex_buffer_.SyncData(func, frame_index);
}

void DynamicModel::SyncMeshData() {
  vertex_buffer_.UploadContents(mesh_->Vertices().data(),
                                mesh_->Vertices().size());
}
}  // namespace GameX::Graphics
