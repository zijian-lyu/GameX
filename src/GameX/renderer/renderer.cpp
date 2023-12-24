#include "GameX/renderer/renderer.h"

#include "GameX/application/application.h"

namespace GameX {

void Renderer::SyncObjects() const {
  if (registered_sync_objects_.empty()) {
    return;
  }

  app_->Core()->SingleTimeCommands([&](VkCommandBuffer cmd_buffer) {
    for (auto sync_object : registered_sync_objects_) {
      sync_object->SyncData(cmd_buffer, app_->Core()->CurrentFrame());
    }
  });
}

Renderer::Renderer(Application *app) : app_(app) {
  CreateDepthRenderPass();
  CreateAssetManager();
  CreateCameraSetLayout();
  CreateEntitySetLayout();
  CreateAmbientLightSetLayout();
  CreateDirectionalLightSetLayout();
  CreateRenderPipeline();
}

Renderer::~Renderer() {
  directional_light_descriptor_set_layout_.reset();
  ambient_light_descriptor_set_layout_.reset();
  render_pipeline_.reset();
  entity_descriptor_set_layout_.reset();
  camera_descriptor_set_layout_.reset();
  asset_manager_.reset();
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
  attachments[0].finalLayout = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL;

  std::vector<VkAttachmentReference> color_attachment_references;
  std::optional<VkAttachmentReference> depth_attachment_reference;
  std::vector<VkAttachmentReference> resolve_attachment_references;

  depth_attachment_reference = VkAttachmentReference{
      0, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};

  depth_render_pass_ = std::make_unique<grassland::vulkan::RenderPass>(
      app_->Core(), attachments, color_attachment_references,
      depth_attachment_reference, resolve_attachment_references);
}

void Renderer::CreateAssetManager() {
  asset_manager_ = std::make_unique<class AssetManager>(this);
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
      std::make_unique<grassland::vulkan::DescriptorSetLayout>(app_->Core(),
                                                               bindings);
}

void Renderer::CreateEntitySetLayout() {
  std::vector<VkDescriptorSetLayoutBinding> bindings;
  bindings.resize(1);
  bindings[0].binding = 0;
  bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  bindings[0].descriptorCount = 1;
  bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  bindings[0].pImmutableSamplers = nullptr;

  entity_descriptor_set_layout_ =
      std::make_unique<grassland::vulkan::DescriptorSetLayout>(app_->Core(),
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
      std::make_unique<grassland::vulkan::DescriptorSetLayout>(app_->Core(),
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
      std::make_unique<grassland::vulkan::DescriptorSetLayout>(app_->Core(),
                                                               bindings);
}

void Renderer::CreateRenderPipeline() {
  render_pipeline_ = std::make_unique<class RenderPipeline>(this);
}

}  // namespace GameX
