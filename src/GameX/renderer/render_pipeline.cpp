#include "GameX/renderer/render_pipeline.h"

#include "GameX/application/application.h"
#include "GameX/renderer/camera.h"
#include "GameX/renderer/entity.h"
#include "GameX/renderer/renderer.h"
#include "GameX/shaders/shaders.h"

namespace GameX {
RenderPipeline::RenderPipeline(struct Renderer *renderer, int max_film)
    : renderer_(renderer) {
  std::vector<VkAttachmentDescription> attachment_descriptions;
  attachment_descriptions.push_back(VkAttachmentDescription{
      0, VK_FORMAT_R32G32B32A32_SFLOAT, VK_SAMPLE_COUNT_1_BIT,
      VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE,
      VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
      VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL});
  attachment_descriptions.push_back(VkAttachmentDescription{
      0, VK_FORMAT_R32G32B32A32_SFLOAT, VK_SAMPLE_COUNT_1_BIT,
      VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE,
      VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
      VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL});
  attachment_descriptions.push_back(VkAttachmentDescription{
      0, VK_FORMAT_R32G32B32A32_SFLOAT, VK_SAMPLE_COUNT_1_BIT,
      VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE,
      VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
      VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL});
  attachment_descriptions.push_back(VkAttachmentDescription{
      0, VK_FORMAT_D32_SFLOAT, VK_SAMPLE_COUNT_1_BIT,
      VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE,
      VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
      VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL});

  std::vector<VkAttachmentReference> color_attachment_references;
  color_attachment_references.push_back(
      VkAttachmentReference{0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL});
  color_attachment_references.push_back(
      VkAttachmentReference{1, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL});
  color_attachment_references.push_back(
      VkAttachmentReference{2, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL});

  std::optional<VkAttachmentReference> depth_attachment_reference =
      VkAttachmentReference{3,
                            VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};

  geometry_pass_render_pass_ = std::make_unique<grassland::vulkan::RenderPass>(
      renderer->App()->Core(), attachment_descriptions,
      color_attachment_references, depth_attachment_reference);

  geometry_pass_vertex_shader_ =
      std::make_unique<grassland::vulkan::ShaderModule>(
          renderer->App()->Core(), BuiltInShaderSpv("geometry_pass.vert"));
  geometry_pass_fragment_shader_ =
      std::make_unique<grassland::vulkan::ShaderModule>(
          renderer->App()->Core(), BuiltInShaderSpv("geometry_pass.frag"));

  geometry_pass_pipeline_layout_ =
      std::make_unique<grassland::vulkan::PipelineLayout>(
          renderer->App()->Core(),
          std::vector<grassland::vulkan::DescriptorSetLayout *>{
              renderer->CameraDescriptorSetLayout(),
              renderer->EntityDescriptorSetLayout()});

  grassland::vulkan::PipelineSettings geometry_pass_pipeline_settings(
      geometry_pass_render_pass_.get(), geometry_pass_pipeline_layout_.get());
  geometry_pass_pipeline_settings.AddShaderStage(
      geometry_pass_vertex_shader_.get(), VK_SHADER_STAGE_VERTEX_BIT);
  geometry_pass_pipeline_settings.AddShaderStage(
      geometry_pass_fragment_shader_.get(), VK_SHADER_STAGE_FRAGMENT_BIT);
  geometry_pass_pipeline_settings.AddInputBinding(0, sizeof(Vertex),
                                                  VK_VERTEX_INPUT_RATE_VERTEX);
  geometry_pass_pipeline_settings.AddInputAttribute(
      0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, position));
  geometry_pass_pipeline_settings.AddInputAttribute(
      0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color));
  geometry_pass_pipeline_settings.AddInputAttribute(
      0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, texCoord));
  geometry_pass_pipeline_settings.AddInputAttribute(
      0, 3, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, normal));
  geometry_pass_pipeline_settings.AddInputAttribute(
      0, 4, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, tangent));

  geometry_pass_pipeline_settings.SetPrimitiveTopology(
      VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

  geometry_pass_pipeline_settings.SetMultiSampleState(VK_SAMPLE_COUNT_1_BIT);

  geometry_pass_pipeline_settings.SetCullMode(VK_CULL_MODE_BACK_BIT);

  geometry_pass_pipeline_ = std::make_unique<grassland::vulkan::Pipeline>(
      renderer->App()->Core(), geometry_pass_pipeline_settings);
}

std::unique_ptr<RenderPipeline::Film> RenderPipeline::CreateFilm(int width,
                                                                 int height) {
  std::unique_ptr<Film> film = std::make_unique<Film>();
  VkExtent2D extent{static_cast<uint32_t>(width),
                    static_cast<uint32_t>(height)};
  film->albedo_image = std::make_unique<grassland::vulkan::Image>(
      renderer_->App()->Core(), VK_FORMAT_R32G32B32A32_SFLOAT, extent,
      VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
  film->normal_image = std::make_unique<grassland::vulkan::Image>(
      renderer_->App()->Core(), VK_FORMAT_R32G32B32A32_SFLOAT, extent,
      VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
  film->position_image = std::make_unique<grassland::vulkan::Image>(
      renderer_->App()->Core(), VK_FORMAT_R32G32B32A32_SFLOAT, extent,
      VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
  film->depth_image = std::make_unique<grassland::vulkan::Image>(
      renderer_->App()->Core(), VK_FORMAT_D32_SFLOAT, extent,
      VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
      VK_IMAGE_ASPECT_DEPTH_BIT);
  film->framebuffer = std::make_unique<grassland::vulkan::Framebuffer>(
      renderer_->App()->Core(), extent, geometry_pass_render_pass_->Handle(),
      std::vector<VkImageView>{
          film->albedo_image->ImageView(), film->normal_image->ImageView(),
          film->position_image->ImageView(), film->depth_image->ImageView()});
  return film;
}

void RenderPipeline::Render(VkCommandBuffer cmd_buffer,
                            const Scene &scene,
                            const Camera &cameras,
                            const RenderPipeline::Film &film) {
  VkRenderPassBeginInfo render_pass_begin_info{};
  render_pass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  render_pass_begin_info.renderPass = geometry_pass_render_pass_->Handle();
  render_pass_begin_info.framebuffer = film.framebuffer->Handle();
  render_pass_begin_info.renderArea.offset = {0, 0};
  render_pass_begin_info.renderArea.extent = film.Extent();
  std::array<VkClearValue, 4> clear_values{};
  clear_values[0].color = {0.0f, 0.0f, 0.0f, 0.0f};
  clear_values[1].color = {0.0f, 0.0f, 0.0f, 0.0f};
  clear_values[2].color = {0.0f, 0.0f, 0.0f, 0.0f};
  clear_values[3].depthStencil = {1.0f, 0};
  render_pass_begin_info.clearValueCount =
      static_cast<uint32_t>(clear_values.size());
  render_pass_begin_info.pClearValues = clear_values.data();
  vkCmdBeginRenderPass(cmd_buffer, &render_pass_begin_info,
                       VK_SUBPASS_CONTENTS_INLINE);
  vkCmdBindPipeline(cmd_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                    geometry_pass_pipeline_->Handle());

  VkDescriptorSet camera_descriptor_set =
      cameras.DescriptorSet(renderer_->App()->Core()->CurrentFrame())->Handle();
  vkCmdBindDescriptorSets(cmd_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                          geometry_pass_pipeline_layout_->Handle(), 0, 1,
                          &camera_descriptor_set, 0, nullptr);

  // Viewport and scissor
  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = film.Extent().width;
  viewport.height = film.Extent().height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  vkCmdSetViewport(cmd_buffer, 0, 1, &viewport);

  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = film.Extent();
  vkCmdSetScissor(cmd_buffer, 0, 1, &scissor);

  for (auto &entity : scene.Entities()) {
    VkDescriptorSet entity_descriptor_set =
        entity->DescriptorSet(renderer_->App()->Core()->CurrentFrame())
            ->Handle();
    vkCmdBindDescriptorSets(cmd_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                            geometry_pass_pipeline_layout_->Handle(), 1, 1,
                            &entity_descriptor_set, 0, nullptr);

    VkBuffer vertex_buffers[] = {
        entity->Model()
            ->VertexBuffer(renderer_->App()->Core()->CurrentFrame())
            ->Handle()};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(cmd_buffer, 0, 1, vertex_buffers, offsets);
    vkCmdBindIndexBuffer(
        cmd_buffer,
        entity->Model()
            ->IndexBuffer(renderer_->App()->Core()->CurrentFrame())
            ->Handle(),
        0, VK_INDEX_TYPE_UINT32);
    vkCmdDrawIndexed(cmd_buffer, entity->Model()->IndexCount(), 1, 0, 0, 0);
  }

  vkCmdEndRenderPass(cmd_buffer);
}
}  // namespace GameX
