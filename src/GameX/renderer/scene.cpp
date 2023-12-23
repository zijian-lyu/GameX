#include "GameX/renderer/scene.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"

namespace GameX {
Scene::Scene(class Renderer *renderer, const SceneSettings &settings) {
  renderer_ = renderer;
  grassland::vulkan::DescriptorPoolSettings descriptor_pool_settings;

  descriptor_pool_ = std::make_unique<grassland::vulkan::DescriptorPool>(
      renderer_->App()->Core(), descriptor_pool_settings);

  CreateCameraSetLayout();
}

void Scene::CreateCameraSetLayout() {
  std::vector<VkDescriptorSetLayoutBinding> bindings;
  bindings.resize(1);
  bindings[0].binding = 0;
  bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  bindings[0].descriptorCount = 1;
  bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  bindings[0].pImmutableSamplers = nullptr;

  camera_descriptor_set_layout_ =
      std::make_unique<grassland::vulkan::DescriptorSetLayout>(
          renderer_->App()->Core(), bindings);
}
}  // namespace GameX
