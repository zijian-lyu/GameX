#include "GameX/renderer/renderer.h"

namespace GameX {
void Renderer::Init() {
  CreatePropertyFilmRenderPass();
}

void Renderer::Update() {
}

void Renderer::Render() {
}

void Renderer::Destroy() {
  property_film_render_pass_.reset();
}

void Renderer::CreatePropertyFilmRenderPass() {
  std::vector<VkAttachmentDescription> attachment_descriptions{};
  std::vector<VkAttachmentReference> color_attachment_references{};
  VkAttachmentReference depth_attachment_reference{};

  attachment_descriptions.push_back(
      {0, VK_FORMAT_R32G32B32_SFLOAT, VK_SAMPLE_COUNT_1_BIT,
       VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE,
       VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
       VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
       VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL});
  color_attachment_references.push_back(
      {0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL});
  attachment_descriptions.push_back(
      {0, VK_FORMAT_R32G32B32_SFLOAT, VK_SAMPLE_COUNT_1_BIT,
       VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE,
       VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
       VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
       VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL});
  color_attachment_references.push_back(
      {1, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL});
  attachment_descriptions.push_back(
      {0, VK_FORMAT_R32G32B32_SFLOAT, VK_SAMPLE_COUNT_1_BIT,
       VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE,
       VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
       VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
       VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL});
  color_attachment_references.push_back(
      {2, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL});
  attachment_descriptions.push_back(
      {0, VK_FORMAT_R32_UINT, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_LOAD,
       VK_ATTACHMENT_STORE_OP_STORE, VK_ATTACHMENT_LOAD_OP_DONT_CARE,
       VK_ATTACHMENT_STORE_OP_DONT_CARE,
       VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
       VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL});
  color_attachment_references.push_back(
      {3, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL});
  attachment_descriptions.push_back(
      {0, VK_FORMAT_R32_UINT, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_LOAD,
       VK_ATTACHMENT_STORE_OP_STORE, VK_ATTACHMENT_LOAD_OP_DONT_CARE,
       VK_ATTACHMENT_STORE_OP_DONT_CARE,
       VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
       VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL});
  color_attachment_references.push_back(
      {4, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL});
  attachment_descriptions.push_back(
      {0, VK_FORMAT_D32_SFLOAT, VK_SAMPLE_COUNT_1_BIT,
       VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE,
       VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
       VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
       VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL});
  depth_attachment_reference = {
      5, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};

  property_film_render_pass_ = std::make_unique<grassland::vulkan::RenderPass>(
      app_->Core(), attachment_descriptions, color_attachment_references,
      depth_attachment_reference);
}
}  // namespace GameX
