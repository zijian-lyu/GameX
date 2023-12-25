#pragma once

#include <thread>

#include "GameX/animation/animation.h"
#include "GameX/core/module.h"
#include "GameX/core/object.h"
#include "GameX/physics/physics.h"

namespace GameX::Base {
class Core : public Module {
 public:
  Core(Animation::Manager *animation_manager);

  ~Core();

  void Start();

  void Stop();

  Animation::Manager *AnimationManager() {
    return animation_manager;
  }

  Physics::World *PhysicsWorld() {
    return physics_world_.get();
  }

 private:
  void LogicThread();

  Animation::Manager *animation_manager;
  std::unique_ptr<Physics::World> physics_world_;

  Metronome metronome_;

  std::thread logic_thread;
  bool stop_logic_thread{false};
};
}  // namespace GameX::Base
