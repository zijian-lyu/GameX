#pragma once

#include <thread>

#include "GameX/animation/animation.h"
#include "GameX/core/module.h"
#include "GameX/core/object.h"
#include "GameX/core/object_manager.h"
#include "GameX/physics/physics.h"

namespace GameX::Base {
class Core : public ObjectManager {
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

  template <class ModuleType, class... Args>
  void LoadModule(Args &&...args) {
    std::lock_guard<std::mutex> lock(load_queue_mutex_);
    load_queue_.push([this, args...]() { new ModuleType(this, args...); });
  }

 private:
  void LogicThread();

  Animation::Manager *animation_manager;
  std::unique_ptr<Physics::World> physics_world_;

  Metronome metronome_;

  std::thread logic_thread_;
  bool stop_logic_thread_{false};

  std::mutex load_queue_mutex_;
  std::queue<std::function<void()>> load_queue_;
};
}  // namespace GameX::Base
