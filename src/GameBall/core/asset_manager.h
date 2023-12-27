#pragma once
#include "GameBall/core/utils.h"

namespace GameBall {
class AssetManager {
 public:
  AssetManager(GameX::Graphics::Renderer *renderer);
  ~AssetManager();
  const GameX::Base::Mesh &MeshFile(const std::string &path);
  GameX::Graphics::PImage ImageFile(const std::string &path);
  GameX::Graphics::PStaticModel StaticModelFile(const std::string &path);

 private:
  GameX::Graphics::Renderer *renderer_;
  std::map<std::string, GameX::Base::Mesh> loaded_meshes_;
  std::map<std::string, GameX::Graphics::UImage> loaded_images_;
  std::map<std::string, GameX::Graphics::UStaticModel> loaded_static_models_;
};
}  // namespace GameBall
