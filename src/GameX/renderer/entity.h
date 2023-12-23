#pragma once
#include "GameX/renderer/scene.h"

namespace GameX {
class Renderer;
class Entity {
 public:
  Entity(Scene *scene) : scene_(scene){};

 private:
  Scene *scene_;
};
}  // namespace GameX
