#pragma once

#include "GameX/utils/utils.h"

namespace GameX {

struct ApplicationSettings {
  bool fullscreen{false};
  int width{1280};
  int height{720};
};

class Application {
 public:
  Application(const ApplicationSettings &settings);

  ~Application();

  GLFWwindow *Window() const {
    return window_;
  }

  grassland::vulkan::Core *Core() const {
    return core_.get();
  }

  void Run();

 private:
  void Init();

  void Update();

  void Render();

  void Cleanup();

  ApplicationSettings settings_;
  GLFWwindow *window_;
  std::unique_ptr<grassland::vulkan::Core> core_;
};
}  // namespace GameX
