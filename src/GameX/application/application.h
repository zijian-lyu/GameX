#pragma once

#include "GameX/physics/physics.h"
#include "GameX/renderer/renderer.h"
#include "GameX/utils/utils.h"

namespace GameX::Base {

struct ApplicationSettings {
  bool fullscreen{false};
  int width{-1};
  int height{-1};
};

class Application {
 public:
  Application(const ApplicationSettings &settings);

  virtual ~Application();

  GLFWwindow *Window() const {
    return window_;
  }

  grassland::vulkan::Core *VkCore() const {
    return vk_core_.get();
  }

  class Renderer *Renderer() const {
    return renderer_.get();
  }

  void Run();

  void OutputImage(VkCommandBuffer cmd_buffer, grassland::vulkan::Image *image);

 private:
  void Init();

  void Update();

  void Render();

  void Cleanup();

  virtual void OnInit() {
  }

  virtual void OnUpdate() {
  }

  virtual void OnRender() {
  }

  virtual void OnCleanup() {
  }

  ApplicationSettings settings_;

  GLFWwindow *window_;

  std::unique_ptr<grassland::vulkan::Core> vk_core_;

  std::unique_ptr<class Renderer> renderer_;
};
}  // namespace GameX::Base
