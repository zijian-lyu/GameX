#include "GameBall/core/asset_manager.h"

namespace GameBall {

AssetManager::AssetManager(GameX::Graphics::Renderer *renderer)
    : renderer_(renderer) {
}

AssetManager::~AssetManager() {
}

GameX::Graphics::Image *AssetManager::ImageFile(const std::string &path) {
  if (loaded_images_.find(path) == loaded_images_.end()) {
    loaded_images_[path] = renderer_->CreateImage(path);
  }
  return loaded_images_.at(path).get();
}

const GameX::Base::Mesh &AssetManager::MeshFile(const std::string &path) {
  if (loaded_meshes_.find(path) == loaded_meshes_.end()) {
    loaded_meshes_[path] = GameX::Base::Mesh(path);
  }
  return loaded_meshes_.at(path);
}

GameX::Graphics::PStaticModel AssetManager::StaticModelFile(
    const std::string &path) {
  if (loaded_static_models_.find(path) == loaded_static_models_.end()) {
    loaded_static_models_[path] = renderer_->CreateStaticModel(MeshFile(path));
  }
  return loaded_static_models_.at(path).get();
}
}  // namespace GameBall
