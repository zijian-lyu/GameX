#include "GameX/animation/model.h"

#include "GameX/animation/animation.h"
#include "GameX/animation/manager.h"

namespace GameX::Animation {

Model::Model(struct Manager *manager) : Object(manager) {
}

StaticModel::StaticModel(struct Manager *manager, const Mesh *mesh)
    : Model(manager) {
  manager_->RecordCommand([this, vertex_buffer = mesh->Vertices(),
                           index_buffer = mesh->Indices()]() {
    model_ = std::make_unique<Base::StaticModel>(
        manager_->Renderer(), Base::Mesh(vertex_buffer, index_buffer));
  });
}

StaticModel::StaticModel(struct Manager *manager, const std::string &path)
    : Model(manager) {
  manager_->RecordCommand([this, path]() {
    model_ = std::make_unique<Base::StaticModel>(manager_->Renderer(),
                                                 Base::Mesh(path));
  });
}

StaticModel::StaticModel(struct Manager *manager, const Base::Mesh &mesh)
    : Model(manager) {
  manager_->RecordCommand([this, mesh]() {
    model_ = std::make_unique<Base::StaticModel>(manager_->Renderer(), mesh);
  });
}

StaticModel::~StaticModel() {
}

DynamicModel::DynamicModel(struct Manager *manager, Mesh *mesh)
    : Model(manager) {
  is_referenced_ = true;
  mesh_ = mesh;
  manager_->RecordCommand([this, ref_mesh = mesh_->ReferenceMesh(),
                           vertices = mesh_->Vertices(),
                           indices = mesh_->Indices()]() {
    ref_mesh->Vertices() = vertices;
    ref_mesh->Indices() = indices;
    model_ =
        std::make_unique<Base::DynamicModel>(manager_->Renderer(), ref_mesh);
  });
}

DynamicModel::DynamicModel(struct Manager *manager, const Base::Mesh &mesh)
    : Model(manager) {
  is_referenced_ = false;
  mesh_ = manager_->CreateMesh(mesh);
  manager_->RecordCommand([this, mesh]() {
    mesh_->ReferenceMesh()->Vertices() = mesh.Vertices();
    mesh_->ReferenceMesh()->Indices() = mesh.Indices();
    model_ = std::make_unique<Base::DynamicModel>(manager_->Renderer(),
                                                  mesh_->ReferenceMesh());
  });
}

DynamicModel::DynamicModel(class GameX::Animation::Manager *manager,
                           const std::string &path)
    : Model(manager) {
  is_referenced_ = false;
  mesh_ = manager_->CreateMesh(path);
  manager_->RecordCommand(
      [this, vertices = mesh_->Vertices(), indices = mesh_->Indices()]() {
        mesh_->ReferenceMesh()->Vertices() = vertices;
        mesh_->ReferenceMesh()->Indices() = indices;
        model_ = std::make_unique<Base::DynamicModel>(manager_->Renderer(),
                                                      mesh_->ReferenceMesh());
      });
}

DynamicModel::~DynamicModel() {
  if (!is_referenced_) {
    delete mesh_;
  }
}

void DynamicModel::SyncMeshData() {
  manager_->RecordCommand([this, vertices = mesh_->Vertices()]() {
    mesh_->ReferenceMesh()->Vertices() = vertices;
    model_->SyncMeshData();
  });
}

}  // namespace GameX::Animation
