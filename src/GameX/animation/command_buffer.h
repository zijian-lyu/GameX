#pragma once
#include <functional>
#include <queue>
#include <set>

#include "GameX/animation/dynamic_object.h"
#include "GameX/animation/object.h"

namespace GameX::Animation {
struct CommandBuffer {
  std::set<Object *> new_objects;
  std::set<DynamicObject *> new_dynamic_objects;
  std::queue<std::function<void(class Manager *)>> commands;
  std::set<Object *> delete_objects;
};
}  // namespace GameX::Animation
