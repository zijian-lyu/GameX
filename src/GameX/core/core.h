#pragma once

#include <thread>

#include "GameX/animation/animation.h"
#include "GameX/physics/physics.h"

namespace GameX::Base {
class Core {
 public:
  Core(Animation::Manager *animation_manager);

  ~Core();

  void Start();

  void Stop();

  Animation::Manager *AnimationManager() {
    return animation_manager;
  }

  Physics::World *PhysicsWorld() {
    return physics_world.get();
  }

 private:
  void LogicThread();

  Animation::Manager *animation_manager;
  std::unique_ptr<Physics::World> physics_world;

  std::thread logic_thread;
};
}  // namespace GameX::Base
