#pragma once

#include "GameX/renderer/camera.h"
#include "GameX/utils/utils.h"

namespace GameX::Graphics {
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

  grassland::vulkan::DescriptorSetLayout *LightingPassDescriptorSetLayout() {
    return lighting_pass_descriptor_set_layout_.get();
  }

  grassland::vulkan::DescriptorPool *LightingPassDescriptorPool() {
    return lighting_pass_descriptor_pool_.get();
  }

  grassland::vulkan::RenderPass *RenderPass() {
    return render_pass_.get();
  }

 private:
  void CreateRenderPass();

  void CreateEnvmapPipeline();

  void CreateGeometryPass();

  void CreateLightingPassCommonAssets(int max_film);

  class Renderer *renderer_;

  std::unique_ptr<grassland::vulkan::RenderPass> render_pass_;
  std::unique_ptr<grassland::vulkan::ShaderModule> geometry_pass_vertex_shader_;
  std::unique_ptr<grassland::vulkan::ShaderModule>
      geometry_pass_fragment_shader_;
  std::unique_ptr<grassland::vulkan::PipelineLayout>
      geometry_pass_pipeline_layout_;
  std::unique_ptr<grassland::vulkan::Pipeline> geometry_pass_pipeline_;

  std::unique_ptr<grassland::vulkan::DescriptorSetLayout>
      lighting_pass_descriptor_set_layout_;
  std::unique_ptr<grassland::vulkan::DescriptorPool>
      lighting_pass_descriptor_pool_;

  std::unique_ptr<grassland::vulkan::ShaderModule> envmap_vertex_shader_;
  std::unique_ptr<grassland::vulkan::ShaderModule> envmap_fragment_shader_;
  std::unique_ptr<grassland::vulkan::PipelineLayout> envmap_pipeline_layout_;
  std::unique_ptr<grassland::vulkan::Pipeline> envmap_pipeline_;

  uint32_t albedo_attachment_index_;
  uint32_t normal_attachment_index_;
  uint32_t position_attachment_index_;
  uint32_t depth_attachment_index_;
  uint32_t output_attachment_index_;
};

typedef RenderPipeline::Film Film;
typedef std::unique_ptr<Film> UFilm;
typedef Film *PFilm;

struct PipelineAssets {
  grassland::vulkan::Pipeline *pipeline;
  grassland::vulkan::PipelineLayout *pipeline_layout;
  grassland::vulkan::ShaderModule *vertex_shader;
  grassland::vulkan::ShaderModule *fragment_shader;
};

}  // namespace GameX::Graphics
