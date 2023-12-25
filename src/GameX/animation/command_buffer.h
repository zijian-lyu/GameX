#pragma once
#include <functional>
#include <queue>
#include <set>

#include "GameX/animation/dynamic_object.h"
#include "GameX/animation/object.h"

namespace GameX::Animation {
struct CommandBuffer {
  std::queue<Object *> new_objects;
  std::queue<DynamicObject *> new_dynamic_objects;
  std::queue<std::function<void()>> commands;
  std::queue<Object *> delete_objects;
};
}  // namespace GameX::Animation
