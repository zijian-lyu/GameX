#pragma once

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

  class Scene *Scene() const {
    return scene_.get();
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
  std::unique_ptr<StaticModel> static_cube_;
  std::unique_ptr<DynamicModel> dynamic_cube_;

  std::unique_ptr<class Scene> scene_;
  std::unique_ptr<Camera> camera_;
  std::unique_ptr<Entity> static_entity_;
  std::unique_ptr<Entity> dynamic_entity_;

  std::unique_ptr<AmbientLight> ambient_light_;

  std::unique_ptr<DirectionalLight> directional_light_;

  std::unique_ptr<RenderPipeline::Film> film_;
};
}  // namespace GameX::Base
