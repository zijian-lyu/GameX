#pragma once
#include "GameX/utils/common.h"
#include "GameX/utils/file.h"

namespace GameX::Base {
class AssetProbe {
 public:
  AssetProbe() {
    search_paths_.emplace_back("");
    search_paths_.emplace_back("assets/");
    search_paths_.emplace_back("../assets/");
    search_paths_.emplace_back(GAMEX_ASSETS_DIR);
  }

  void AddSearchPath(const std::string &path) {
    search_paths_.push_back(path);
  }

  std::string ProbeAsset(const std::string &asset_name) const {
    for (const auto &path : search_paths_) {
      std::string full_path = path + asset_name;
      if (FileExists(full_path)) {
        return full_path;
      }
    }
    return "";
  }

  static AssetProbe *PublicInstance() {
    static AssetProbe probe;
    return &probe;
  }

 private:
  std::vector<std::string> search_paths_;
};
}  // namespace GameX::Base
