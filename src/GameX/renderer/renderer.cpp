#include "GameX/renderer/renderer.h"

#include "GameX/application/application.h"

namespace GameX::Graphics {

void Renderer::SyncObjects() const {
  if (registered_sync_objects_.empty()) {
    return;
  }

  app_->VkCore()->SingleTimeCommands([&](VkCommandBuffer cmd_buffer) {
    for (auto sync_object : registered_sync_objects_) {
      sync_object->SyncData(cmd_buffer, app_->VkCore()->CurrentFrame());
    }
  });
}

Renderer::Renderer(Base::Application *app) : app_(app) {
  CreateDepthRenderPass();
  CreateCameraSetLayout();
  CreateEntitySetLayout();
  CreateAmbientLightSetLayout();
  CreateDirectionalLightSetLayout();
  CreateRenderPipeline();
  CreateDefaultImagesAndSamplers();
}

Renderer::~Renderer() {
  linear_sampler_.reset();
  nearest_sampler_.reset();
  anisotropic_sampler_.reset();
  directional_light_descriptor_set_layout_.reset();
  ambient_light_descriptor_set_layout_.reset();
  render_pipeline_.reset();
  entity_descriptor_set_layout_.reset();
  camera_descriptor_set_layout_.reset();
  depth_render_pass_.reset();
}

void Renderer::CreateDepthRenderPass() {
  std::vector<VkAttachmentDescription> attachments(1);

  attachments[0].format = VK_FORMAT_D32_SFLOAT;
  attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
  attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  attachments[0].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

  std::vector<VkAttachmentReference> color_attachment_references;
  std::optional<VkAttachmentReference> depth_attachment_reference;
  std::vector<VkAttachmentReference> resolve_attachment_references;

  depth_attachment_reference = VkAttachmentReference{
      0, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};

  depth_render_pass_ = std::make_unique<grassland::vulkan::RenderPass>(
      app_->VkCore(), attachments, color_attachment_references,
      depth_attachment_reference, resolve_attachment_references);
}

void Renderer::CreateCameraSetLayout() {
  std::vector<VkDescriptorSetLayoutBinding> bindings;
  bindings.resize(1);
  bindings[0].binding = 0;
  bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  bindings[0].descriptorCount = 1;
  bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  bindings[0].pImmutableSamplers = nullptr;

  camera_descriptor_set_layout_ =
      std::make_unique<grassland::vulkan::DescriptorSetLayout>(app_->VkCore(),
                                                               bindings);
}

void Renderer::CreateEntitySetLayout() {
  std::vector<VkDescriptorSetLayoutBinding> bindings;
  bindings.resize(2);
  bindings[0].binding = 0;
  bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  bindings[0].descriptorCount = 1;
  bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  bindings[0].pImmutableSamplers = nullptr;

  // TODO: Add texture sampler
  bindings[1].binding = 1;
  bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  bindings[1].descriptorCount = 1;
  bindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  bindings[1].pImmutableSamplers = nullptr;

  entity_descriptor_set_layout_ =
      std::make_unique<grassland::vulkan::DescriptorSetLayout>(app_->VkCore(),
                                                               bindings);
}

void Renderer::CreateAmbientLightSetLayout() {
  std::vector<VkDescriptorSetLayoutBinding> bindings;
  bindings.resize(1);
  bindings[0].binding = 0;
  bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  bindings[0].descriptorCount = 1;
  bindings[0].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  bindings[0].pImmutableSamplers = nullptr;

  ambient_light_descriptor_set_layout_ =
      std::make_unique<grassland::vulkan::DescriptorSetLayout>(app_->VkCore(),
                                                               bindings);
}

void Renderer::CreateDirectionalLightSetLayout() {
  std::vector<VkDescriptorSetLayoutBinding> bindings;
  bindings.resize(1);
  bindings[0].binding = 0;
  bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  bindings[0].descriptorCount = 1;
  bindings[0].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  bindings[0].pImmutableSamplers = nullptr;

  directional_light_descriptor_set_layout_ =
      std::make_unique<grassland::vulkan::DescriptorSetLayout>(app_->VkCore(),
                                                               bindings);
}

void Renderer::CreateRenderPipeline() {
  render_pipeline_ = std::make_unique<class RenderPipeline>(this);
}

void Renderer::CreateDefaultImagesAndSamplers() {
  linear_sampler_ = std::make_unique<grassland::vulkan::Sampler>(
      app_->VkCore(), VK_FILTER_LINEAR, VK_FILTER_LINEAR,
      VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
      VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
      VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, VK_FALSE,
      VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK, VK_SAMPLER_MIPMAP_MODE_LINEAR);
  nearest_sampler_ = std::make_unique<grassland::vulkan::Sampler>(
      app_->VkCore(), VK_FILTER_NEAREST, VK_FILTER_NEAREST,
      VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
      VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
      VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, VK_FALSE,
      VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK, VK_SAMPLER_MIPMAP_MODE_NEAREST);
  anisotropic_sampler_ = std::make_unique<grassland::vulkan::Sampler>(
      app_->VkCore(), VK_FILTER_LINEAR, VK_FILTER_LINEAR,
      VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_SAMPLER_ADDRESS_MODE_REPEAT,
      VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_TRUE,
      VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK, VK_SAMPLER_MIPMAP_MODE_LINEAR);

  Base::Image white_image(1, 1, Base::Pixel{255, 255, 255, 255});
  Base::Image normal_map_image(1, 1, Base::Pixel{128, 128, 255, 255});
  Base::Image black_image(1, 1, Base::Pixel{0, 0, 0, 255});
  white_image_ = CreateImage(white_image);
  normal_map_image_ = CreateImage(normal_map_image);
  black_image_ = CreateImage(black_image);
}

}  // namespace GameX::Graphics
