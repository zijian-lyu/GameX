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

StaticModel::StaticModel(Renderer *renderer, const std::string &path)
    : StaticModel(renderer, Base::Mesh(path)) {
}

AnimatedModel::AnimatedModel(Renderer *renderer, Base::Mesh *mesh)
    : Model(renderer), mesh_(mesh) {
  is_referenced_ = true;
  vertex_buffer_.Init(renderer_->App()->VkCore(), mesh->Vertices().size());
  vertex_buffer_.UploadContents(mesh->Vertices().data(),
                                mesh->Vertices().size());
  index_buffer_.Init(renderer_->App()->VkCore(), mesh->Indices().size());
  index_buffer_.UploadContents(mesh->Indices().data(), mesh->Indices().size());

  renderer_->RegisterSyncObject(&vertex_buffer_);
}

AnimatedModel::~AnimatedModel() {
  if (!is_referenced_) {
    delete mesh_;
  }
  renderer_->UnregisterSyncObject(&vertex_buffer_);
}

bool AnimatedModel::SyncData(VkCommandBuffer cmd_buffer) {
  ;
  return SyncData(cmd_buffer, renderer_->App()->VkCore()->CurrentFrame());
}

bool AnimatedModel::SyncData(std::function<void(VkCommandBuffer)> &func) {
  return SyncData(func, renderer_->App()->VkCore()->CurrentFrame());
}

bool AnimatedModel::SyncData(VkCommandBuffer cmd_buffer, uint32_t frame_index) {
  return vertex_buffer_.SyncData(cmd_buffer, frame_index);
}

bool AnimatedModel::SyncData(std::function<void(VkCommandBuffer)> &func,
                             uint32_t frame_index) {
  return vertex_buffer_.SyncData(func, frame_index);
}

void AnimatedModel::SyncMeshData() {
  vertex_buffer_.UploadContents(mesh_->Vertices().data(),
                                mesh_->Vertices().size());
}
}  // namespace GameX::Graphics
