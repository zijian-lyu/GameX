#pragma once

#include "GameX/renderer/asset_manager.h"
#include "GameX/renderer/camera.h"
#include "GameX/renderer/model.h"
#include "GameX/renderer/scene.h"
#include "GameX/utils/utils.h"

namespace GameX {
class Application;

class Renderer {
 public:
  Renderer(Application *app);

  Application *App() const {
    return app_;
  }

  void RegisterSyncObject(grassland::vulkan::DynamicObject *sync_object) {
    registered_sync_objects_.insert(sync_object);
  }

  void UnregisterSyncObject(grassland::vulkan::DynamicObject *sync_object) {
    registered_sync_objects_.erase(sync_object);
  }

  grassland::vulkan::RenderPass *DepthRenderPass() const {
    return depth_render_pass_.get();
  }

  AssetManager *AssetManager() const {
    return asset_manager_.get();
  }

  void SyncObjects() const;

 private:
  void CreateDepthRenderPass();
  void CreateAssetManager();

  Application *app_;
  std::set<grassland::vulkan::DynamicObject *> registered_sync_objects_;
  std::unique_ptr<grassland::vulkan::RenderPass> depth_render_pass_;
  std::unique_ptr<class AssetManager> asset_manager_;
};
}  // namespace GameX
