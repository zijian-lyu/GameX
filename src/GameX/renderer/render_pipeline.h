#pragma once

#include "GameX/renderer/camera.h"
#include "GameX/utils/utils.h"

namespace GameX {
class RenderPipeline {
 public:
  RenderPipeline(class Renderer *renderer, int max_film = 1024);

  struct Film {
    std::unique_ptr<grassland::vulkan::Image> albedo_image;
    std::unique_ptr<grassland::vulkan::Image> normal_image;
    std::unique_ptr<grassland::vulkan::Image> position_image;
    std::unique_ptr<grassland::vulkan::Image> depth_image;
    std::unique_ptr<grassland::vulkan::Framebuffer> framebuffer;

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
  class Renderer *renderer_;
  std::unique_ptr<grassland::vulkan::ShaderModule> geometry_pass_vertex_shader_;
  std::unique_ptr<grassland::vulkan::ShaderModule>
      geometry_pass_fragment_shader_;
  std::unique_ptr<grassland::vulkan::ShaderModule> lighting_pass_vertex_shader_;
  std::unique_ptr<grassland::vulkan::ShaderModule>
      lighting_pass_fragment_shader_;
  std::unique_ptr<grassland::vulkan::RenderPass> geometry_pass_render_pass_;
  std::unique_ptr<grassland::vulkan::RenderPass> lighting_pass_render_pass_;
  std::unique_ptr<grassland::vulkan::PipelineLayout>
      geometry_pass_pipeline_layout_;
  std::unique_ptr<grassland::vulkan::PipelineLayout>
      lighting_pass_pipeline_layout_;
  std::unique_ptr<grassland::vulkan::Pipeline> geometry_pass_pipeline_;
  std::unique_ptr<grassland::vulkan::Pipeline> lighting_pass_pipeline_;

  std::unique_ptr<grassland::vulkan::DescriptorSetLayout>
      lighting_pass_descriptor_set_layout_;
  std::unique_ptr<grassland::vulkan::DescriptorPool>
      lighting_pass_descriptor_pool_;
};
}  // namespace GameX
