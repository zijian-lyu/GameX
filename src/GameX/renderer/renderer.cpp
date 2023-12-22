#include "GameX/renderer/renderer.h"

#include "GameX/application/application.h"

namespace GameX {

void Renderer::SyncObjects() const {
  if (registered_sync_objects_.empty()) {
    return;
  }

  app_->Core()->SingleTimeCommands([&](VkCommandBuffer cmd_buffer) {
    for (auto sync_object : registered_sync_objects_) {
      sync_object->SyncData(cmd_buffer, app_->Core()->CurrentFrame());
    }
  });
}
}  // namespace GameX
