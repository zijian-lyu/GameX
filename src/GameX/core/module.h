#pragma once
#include <queue>

#include "GameX/core/object.h"

namespace GameX::Base {
class Module {
 public:
  Module();
  ~Module();

 protected:
  void UpdateSubordinates();

 private:
  friend Object;
  void RegisterSubordinate(Object *subordinate);

  void UnregisterSubordinate(Object *subordinate);

  void RegisterDependency(Object *subordinate, Object *dependency);

  void UnregisterDependency(Object *subordinate, Object *dependency);

  bool CycleCheck() const;

  std::map<Object *, std::set<Object *>> subordinate_dependencies_{};
  std::map<Object *, uint32_t> dependency_count_{};
};
}  // namespace GameX::Base
