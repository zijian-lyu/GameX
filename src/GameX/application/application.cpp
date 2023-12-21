#include "GameX/application/application.h"

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
}

void Application::Update() {
}

void Application::Render() {
}

void Application::Cleanup() {
}
}  // namespace GameX
