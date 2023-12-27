#pragma once
#include "GameX/renderer/light.h"

namespace GameX::Graphics {
GAMEX_DECLARE_CLASS(Scene)
GAMEX_CLASS(AmbientLight) : public Light {
 public:
  struct AmbientLightData {
    glm::vec3 color;
    float intensity;
  };

  AmbientLight(PScene scene, const AmbientLightData &settings = {});

  AmbientLight(PScene scene, glm::vec3 color, float intensity = 1.0f);

  ~AmbientLight();

  grassland::vulkan::Pipeline *LightingPipeline() override;

  void Lighting(VkCommandBuffer cmd_buffer, int frame_index) override;

  void SetLight(glm::vec3 color = glm::vec3{0.3f}, float intensity = 1.0f);

 private:
  std::unique_ptr<grassland::vulkan::DynamicBuffer<AmbientLightData>> buffer_;
  std::vector<std::unique_ptr<grassland::vulkan::DescriptorSet>>
      descriptor_sets_;
};

grassland::vulkan::DescriptorSetLayout *AmbientLightDescriptorSetLayout(
    class Renderer *renderer);

grassland::vulkan::Pipeline *AmbientLightPipeline(class Renderer *renderer);
}  // namespace GameX::Graphics
