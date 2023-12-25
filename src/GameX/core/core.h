#pragma once
#include <thread>

#include "GameX/animation/animation.h"
#include "GameX/physics/physics.h"

namespace GameX::Base {
class Core {
 public:
  Core();
  ~Core();
  void Start();
  void Stop();

 private:
  void LogicThread();

  std::thread logic_thread;
};
}  // namespace GameX::Base
