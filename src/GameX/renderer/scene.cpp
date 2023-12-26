#include "GameX/renderer/scene.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"

namespace GameX::Graphics {
Scene::Scene(class Renderer *renderer, const SceneSettings &settings) {
  renderer_ = renderer;
  grassland::vulkan::DescriptorPoolSettings descriptor_pool_settings;

  descriptor_pool_ = std::make_unique<grassland::vulkan::DescriptorPool>(
      renderer_->App()->VkCore(), descriptor_pool_settings);

  renderer_->RegisterSyncObject(this);

  envmap_versions_.resize(renderer_->App()->VkCore()->MaxFramesInFlight(), 0);
  staging_envmap_version_ = 0;
}

Scene::~Scene() {
  renderer_->UnregisterSyncObject(this);
}

bool Scene::SyncData(VkCommandBuffer cmd_buffer, uint32_t frame_index) {
  return false;
}

}  // namespace GameX::Graphics
