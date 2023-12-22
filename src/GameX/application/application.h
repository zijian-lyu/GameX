#pragma once

#include "GameX/renderer/renderer.h"
#include "GameX/utils/utils.h"

namespace GameX {

struct ApplicationSettings {
  bool fullscreen{false};
  int width{-1};
  int height{-1};
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

  class Renderer *Renderer() const {
    return renderer_.get();
  }

  void Run();

 private:
  void Init();

  void Update();

  void Render();

  void Cleanup();

  void CreateCube();

  ApplicationSettings settings_;

  GLFWwindow *window_;
  std::unique_ptr<grassland::vulkan::Core> core_;

  std::unique_ptr<class Renderer> renderer_;

  Mesh cube_;
  std::unique_ptr<StaticObject> static_cube_;
  std::unique_ptr<DynamicObject> dynamic_cube_;
};
}  // namespace GameX
