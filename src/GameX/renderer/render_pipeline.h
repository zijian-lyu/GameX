#pragma once

#include "GameX/renderer/camera.h"
#include "GameX/utils/utils.h"

namespace GameX {
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

 private:
  void CreateRenderPass();
  void CreateGeometryPass();
  void CreateLightingPassCommonAssets(int max_film);
  void CreateLightAmbientPipeline();

  class Renderer *renderer_;
  std::unique_ptr<grassland::vulkan::RenderPass> render_pass_;
  std::unique_ptr<grassland::vulkan::ShaderModule> geometry_pass_vertex_shader_;
  std::unique_ptr<grassland::vulkan::ShaderModule>
      geometry_pass_fragment_shader_;
  std::unique_ptr<grassland::vulkan::PipelineLayout>
      geometry_pass_pipeline_layout_;
  std::unique_ptr<grassland::vulkan::Pipeline> geometry_pass_pipeline_;

  std::unique_ptr<grassland::vulkan::ShaderModule> light_ambient_vertex_shader_;
  std::unique_ptr<grassland::vulkan::ShaderModule>
      light_ambient_fragment_shader_;
  std::unique_ptr<grassland::vulkan::PipelineLayout>
      light_ambient_pipeline_layout_;
  std::unique_ptr<grassland::vulkan::Pipeline> light_ambient_pipeline_;

  std::unique_ptr<grassland::vulkan::DescriptorSetLayout>
      lighting_pass_descriptor_set_layout_;
  std::unique_ptr<grassland::vulkan::DescriptorPool>
      lighting_pass_descriptor_pool_;
};
}  // namespace GameX
