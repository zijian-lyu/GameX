#include "GameX/application/application.h"

#include "GameX/renderer/renderer.h"

namespace GameX {
Application::Application(const GameX::ApplicationSettings &settings)
    : settings_(settings) {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window_ = glfwCreateWindow(settings_.width, settings_.height, "GameX",
                             nullptr, nullptr);

  grassland::vulkan::CoreSettings core_settings;
  core_settings.window = window_;

  core_ = std::make_unique<grassland::vulkan::Core>(core_settings);
}

Application::~Application() {
  core_.reset();
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void Application::Run() {
  Init();

  while (!glfwWindowShouldClose(window_)) {
    glfwPollEvents();
    Update();
    Render();
  }

  core_->Device()->WaitIdle();
  Cleanup();
}

void Application::Init() {
  int frame_width, frame_height;
  glfwGetFramebufferSize(window_, &frame_width, &frame_height);
}

void Application::Update() {
}

void Application::Render() {
  core_->BeginFrame();

  auto cmd_buffer = core_->CommandBuffer();

  auto frame_image = core_->SwapChain()->Images()[core_->ImageIndex()];

  // Transition frame_image_ to VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
  grassland::vulkan::TransitImageLayout(
      cmd_buffer->Handle(), frame_image, VK_IMAGE_LAYOUT_UNDEFINED,
      VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
      VK_PIPELINE_STAGE_TRANSFER_BIT, VK_ACCESS_MEMORY_READ_BIT,
      VK_ACCESS_TRANSFER_WRITE_BIT, VK_IMAGE_ASPECT_COLOR_BIT);

  // Clear frame_image_ to black
  VkClearColorValue clear_color{0.0f, 0.0f, 0.0f, 1.0f};
  VkImageSubresourceRange subresource_range{VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0,
                                            1};

  vkCmdClearColorImage(cmd_buffer->Handle(), frame_image,
                       VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clear_color, 1,
                       &subresource_range);

  // Transition frame_image_ to VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
  grassland::vulkan::TransitImageLayout(
      cmd_buffer->Handle(), frame_image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_PIPELINE_STAGE_TRANSFER_BIT,
      VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_ACCESS_TRANSFER_WRITE_BIT,
      VK_ACCESS_MEMORY_READ_BIT, VK_IMAGE_ASPECT_COLOR_BIT);

  core_->EndFrame();
}

void Application::Cleanup() {
}
}  // namespace GameX
