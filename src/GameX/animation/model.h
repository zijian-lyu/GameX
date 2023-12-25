#pragma once
#include "GameX/animation/mesh.h"
#include "GameX/animation/object.h"

namespace GameX::Animation {

class Model : public Object {
 public:
  Model(class Manager *manager);

  ~Model() override = default;

  virtual GameX::Base::Model *Handle() = 0;
};

class StaticModel : public Model {
 public:
  StaticModel(class Manager *manager, const Mesh *mesh);
  StaticModel(class Manager *manager, const Base::Mesh &mesh);
  StaticModel(class Manager *manager, const std::string &path);

  ~StaticModel() override;

  GameX::Base::Model *Handle() override {
    return model_.get();
  }

 private:
  std::unique_ptr<GameX::Base::StaticModel> model_;
};

class DynamicModel : public Model {
 public:
  DynamicModel(class Manager *manager, Mesh *mesh);
  DynamicModel(class Manager *manager, const Base::Mesh &mesh);
  DynamicModel(class Manager *manager, const std::string &path);

  ~DynamicModel() override;

  GameX::Base::Model *Handle() override {
    return model_.get();
  }

  std::vector<Base::Vertex> &Vertices() {
    return mesh_->Vertices();
  }

  const std::vector<Base::Vertex> &Vertices() const {
    return mesh_->Vertices();
  }

  std::vector<uint32_t> &Indices() {
    return mesh_->Indices();
  }

  const std::vector<uint32_t> &Indices() const {
    return mesh_->Indices();
  }

  void SyncMeshData();

 private:
  bool is_referenced_{};
  Mesh *mesh_;
  std::unique_ptr<GameX::Base::DynamicModel> model_;
};

}  // namespace GameX::Animation
