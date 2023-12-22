#pragma once

#include "GameX/renderer/geometry_buffer.h"
#include "GameX/renderer/object.h"
#include "GameX/renderer/scene.h"
#include "GameX/utils/utils.h"

namespace GameX {
class Application;

class Renderer {
 public:
  Renderer(Application *app) : app_(app) {
  }

  Application *App() const {
    return app_;
  }

  void RegisterSyncObject(grassland::vulkan::DynamicObject *sync_object) {
    registered_sync_objects_.insert(sync_object);
  }

  void UnregisterSyncObject(grassland::vulkan::DynamicObject *sync_object) {
    registered_sync_objects_.erase(sync_object);
  }

  void SyncObjects() const;

 private:
  Application *app_;
  std::set<grassland::vulkan::DynamicObject *> registered_sync_objects_;
};
}  // namespace GameX
