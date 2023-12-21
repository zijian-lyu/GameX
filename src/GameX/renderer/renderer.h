#pragma once

#include "GameX/application/application.h"
#include "GameX/utils/utils.h"

namespace GameX {
class Renderer {
 public:
  Renderer(Application *app) : app_(app) {
  }

  void Init();

  void Update();

  void Render();

  void Destroy();

  Application *App() const {
    return app_;
  }

  grassland::vulkan::RenderPass *PropertyFilmRenderPass() const {
    return property_film_render_pass_.get();
  }

 private:
  void CreatePropertyFilmRenderPass();
  Application *app_;
  std::unique_ptr<grassland::vulkan::RenderPass> property_film_render_pass_;
};
}  // namespace GameX
