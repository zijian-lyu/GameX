#pragma once

#include <iostream>

#include "GameX/renderer/camera.h"
#include "GameX/renderer/lights/lights.h"
#include "GameX/renderer/model.h"
#include "GameX/renderer/render_pipeline.h"
#include "GameX/renderer/scene.h"
#include "GameX/utils/utils.h"

namespace GameX::Base {
class Application;

class Renderer {
 public:
  Renderer(Application *app);

  ~Renderer();

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

  grassland::vulkan::DescriptorSetLayout *CameraDescriptorSetLayout() {
    return camera_descriptor_set_layout_.get();
  }

  grassland::vulkan::DescriptorSetLayout *EntityDescriptorSetLayout() {
    return entity_descriptor_set_layout_.get();
  }

  grassland::vulkan::DescriptorSetLayout *AmbientLightDescriptorSetLayout() {
    return ambient_light_descriptor_set_layout_.get();
  }

  grassland::vulkan::DescriptorSetLayout *
  DirectionalLightDescriptorSetLayout() {
    return directional_light_descriptor_set_layout_.get();
  }

  RenderPipeline *RenderPipeline() const {
    return render_pipeline_.get();
  }

  void SyncObjects() const;

 private:
  void CreateDepthRenderPass();
  void CreateCameraSetLayout();
  void CreateEntitySetLayout();
  void CreateAmbientLightSetLayout();
  void CreateDirectionalLightSetLayout();
  void CreateRenderPipeline();

  Application *app_;
  std::set<grassland::vulkan::DynamicObject *> registered_sync_objects_;
  std::unique_ptr<grassland::vulkan::DescriptorSetLayout>
      camera_descriptor_set_layout_;
  std::unique_ptr<grassland::vulkan::DescriptorSetLayout>
      entity_descriptor_set_layout_;
  std::unique_ptr<grassland::vulkan::DescriptorSetLayout>
      ambient_light_descriptor_set_layout_;
  std::unique_ptr<grassland::vulkan::DescriptorSetLayout>
      directional_light_descriptor_set_layout_;
  std::unique_ptr<grassland::vulkan::RenderPass> depth_render_pass_;
  std::unique_ptr<class RenderPipeline> render_pipeline_;
};
}  // namespace GameX::Base
