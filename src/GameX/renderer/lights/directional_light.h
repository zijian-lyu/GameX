#pragma once
#include "GameX/renderer/light.h"

namespace GameX::Graphics {
GAMEX_CLASS(DirectionalLight) : public Light {
 public:
  struct DirectionalLightData {
    glm::vec3 color;
    float intensity;
    glm::vec3 direction;
  };

  DirectionalLight(class Scene * scene,
                   const DirectionalLightData &settings = {});

  DirectionalLight(class Scene * scene, glm::vec3 color,
                   glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f),
                   float intensity = 1.0f);

  ~DirectionalLight();

  grassland::vulkan::Pipeline *LightingPipeline() override;

  void Lighting(VkCommandBuffer cmd_buffer, int frame_index) override;

  void SetLight(glm::vec3 color = glm::vec3{0.3f},
                glm::vec3 direction = glm::vec3(0.0f, 1.0f, 0.0f),
                float intensity = 1.0f);

 private:
  std::unique_ptr<grassland::vulkan::DynamicBuffer<DirectionalLightData>>
      buffer_;
  std::vector<std::unique_ptr<grassland::vulkan::DescriptorSet>>
      descriptor_sets_;
};

grassland::vulkan::DescriptorSetLayout *DirectionalLightDescriptorSetLayout(
    class Renderer *renderer);

grassland::vulkan::Pipeline *DirectionalLightPipeline(class Renderer *renderer);
}  // namespace GameX::Graphics
