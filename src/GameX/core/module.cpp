#include "GameX/core/module.h"

namespace GameX::Base {
Module::Module() {
}

void Module::RegisterSubordinate(Object *subordinate) {
  subordinate_dependencies_[subordinate] = {};
  dependency_count_[subordinate] = 0;
}

void Module::UnregisterSubordinate(Object *subordinate) {
  if (subordinate_dependencies_.find(subordinate) ==
      subordinate_dependencies_.end()) {
    LAND_ERROR("Subordinate not found");
  }

  for (auto &dependency : subordinate_dependencies_[subordinate]) {
    dependency_count_[dependency]--;
  }

  subordinate_dependencies_.erase(subordinate);
  dependency_count_.erase(subordinate);

  for (auto &dependency : subordinate_dependencies_) {
    dependency.second.erase(subordinate);
  }
}

void Module::RegisterDependency(Object *subordinate, Object *dependency) {
  if (subordinate_dependencies_.find(dependency) !=
      subordinate_dependencies_.end()) {
    subordinate_dependencies_[dependency].insert(subordinate);
    dependency_count_[subordinate]++;
    if (CycleCheck()) {
      subordinate_dependencies_[dependency].erase(subordinate);
      LAND_ERROR("Cycle dependency detected");
    }
  }
}

void Module::UnregisterDependency(Object *subordinate, Object *dependency) {
  if (subordinate_dependencies_.find(dependency) !=
      subordinate_dependencies_.end()) {
    subordinate_dependencies_[dependency].erase(subordinate);
    dependency_count_[subordinate]--;
  } else {
    LAND_ERROR("Dependency not found");
  }
}

bool Module::CycleCheck() const {
  std::set<Object *> visited;
  std::function<bool(Object *)> dfs = [&](Object *object) {
    if (visited.find(object) != visited.end()) {
      return true;
    }
    visited.insert(object);
    for (auto &subordinate : subordinate_dependencies_.at(object)) {
      if (dfs(subordinate)) {
        return true;
      }
    }
    return false;
  };
  bool result = false;
  for (auto &subordinate : subordinate_dependencies_) {
    if (dfs(subordinate.first)) {
      result = true;
      break;
    }
  }
  return result;
}

void Module::UpdateSubordinates() {
  std::map<Object *, uint32_t> dependency_count = dependency_count_;
  std::queue<Object *> updating_objects;

  for (auto &dependency : dependency_count) {
    if (dependency.second == 0) {
      updating_objects.push(dependency.first);
    }
  }

  while (!updating_objects.empty()) {
    auto &object = updating_objects.front();
    object->Update();
    for (auto &subordinate : subordinate_dependencies_[object]) {
      dependency_count[subordinate]--;
      if (dependency_count[subordinate] == 0) {
        updating_objects.push(subordinate);
      }
    }
    updating_objects.pop();
  }
}

Module::~Module() {
  if (!subordinate_dependencies_.empty()) {
    LAND_ERROR("Module is not empty");
  }
}
}  // namespace GameX::Base
