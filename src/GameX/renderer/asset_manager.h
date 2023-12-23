#pragma once
#include "GameX/utils/utils.h"

namespace GameX {
class Renderer;
class AssetManager {
 public:
  AssetManager(Renderer *renderer) : renderer_(renderer) {
    asset_paths_.emplace_back("assets/");
    asset_paths_.emplace_back("../assets/");
    asset_paths_.emplace_back(GAMEX_ASSETS_DIR);
  }

  void AddAssetPath(const std::string &path) {
    asset_paths_.push_back(path);
  }

  std::string GetAssetPath(const std::string &asset_name) const {
    for (const auto &path : asset_paths_) {
      std::string full_path = path + asset_name;
      if (FileExists(full_path)) {
        return full_path;
      }
    }
    return "";
  }

 private:
  Renderer *renderer_;
  std::vector<std::string> asset_paths_;
};
}  // namespace GameX
