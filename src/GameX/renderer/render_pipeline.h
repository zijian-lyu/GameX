#pragma once

#include "GameX/renderer/camera.h"
#include "GameX/utils/utils.h"

namespace GameX::Base {
class RenderPipeline {
 public:
  RenderPipeline(class Renderer *renderer, int max_film = 1024);

  struct Film {
    static constexpr int kNumGBufferInputAttachments = 3;
    std::unique_ptr<grassland::vulkan::Image> albedo_image;
    std::unique_ptr<grassland::vulkan::Image> normal_image;
    std::unique_ptr<grassland::vulkan::Image> position_image;
    std::unique_ptr<grassland::vulkan::Image> depth_image;

    std::unique_ptr<grassland::vulkan::Image> output_image;

    std::unique_ptr<grassland::vulkan::Framebuffer> framebuffer;
    std::unique_ptr<grassland::vulkan::DescriptorSet> input_attachment_set;

    VkExtent2D Extent() const {
      return albedo_image->Extent();
    }
  };

  std::unique_ptr<Film> CreateFilm(int width, int height);

  void Render(VkCommandBuffer cmd_buffer,
              const Scene &scene,
              const Camera &cameras,
              const Film &film);

  grassland::vulkan::Pipeline *AmbientLightPipeline() {
    return ambient_light_pipeline_.get();
  }

  grassland::vulkan::Pipeline *DirectionalLightPipeline() {
    return directional_light_pipeline_.get();
  }

 private:
  void CreateRenderPass();
  void CreateGeometryPass();
  void CreateLightingPassCommonAssets(int max_film);
  void CreateAmbientLightPipeline();
  void CreateDirectionalLightPipeline();

  class Renderer *renderer_;
  std::unique_ptr<grassland::vulkan::RenderPass> render_pass_;
  std::unique_ptr<grassland::vulkan::ShaderModule> geometry_pass_vertex_shader_;
  std::unique_ptr<grassland::vulkan::ShaderModule>
      geometry_pass_fragment_shader_;
  std::unique_ptr<grassland::vulkan::PipelineLayout>
      geometry_pass_pipeline_layout_;
  std::unique_ptr<grassland::vulkan::Pipeline> geometry_pass_pipeline_;

  std::unique_ptr<grassland::vulkan::ShaderModule> ambient_light_vertex_shader_;
  std::unique_ptr<grassland::vulkan::ShaderModule>
      ambient_light_fragment_shader_;
  std::unique_ptr<grassland::vulkan::PipelineLayout>
      ambient_light_pipeline_layout_;
  std::unique_ptr<grassland::vulkan::Pipeline> ambient_light_pipeline_;

  std::unique_ptr<grassland::vulkan::ShaderModule>
      directional_light_vertex_shader_;
  std::unique_ptr<grassland::vulkan::ShaderModule>
      directional_light_fragment_shader_;
  std::unique_ptr<grassland::vulkan::PipelineLayout>
      directional_light_pipeline_layout_;
  std::unique_ptr<grassland::vulkan::Pipeline> directional_light_pipeline_;

  std::unique_ptr<grassland::vulkan::DescriptorSetLayout>
      lighting_pass_descriptor_set_layout_;
  std::unique_ptr<grassland::vulkan::DescriptorPool>
      lighting_pass_descriptor_pool_;

  uint32_t albedo_attachment_index_;
  uint32_t normal_attachment_index_;
  uint32_t position_attachment_index_;
  uint32_t depth_attachment_index_;
  uint32_t output_attachment_index_;
};
}  // namespace GameX::Base
