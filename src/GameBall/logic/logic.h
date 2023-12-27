#pragma once
#include "GameBall/logic/unit.h"
#include "GameBall/logic/world.h"

namespace GameBall::Logic {
class Manager {
 public:
  Manager();
  ~Manager();

  class World *World() const;
  void Start();
  void Stop();

 private:
  friend ::GameBall::GameBall;
  void LogicThread();

  std::unique_ptr<class World> world_;
  std::thread logic_thread_;
  std::unique_ptr<GameX::Base::Metronome> metronome_;
  std::mutex logic_mutex_;
  bool stop_signal_{false};
};
}  // namespace GameBall::Logic
