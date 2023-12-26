#include "GameX/core/core.h"

namespace GameX::Base {

Core::Core(Animation::Manager *animation_manager)
    : animation_manager(animation_manager) {
  physics_world_ = std::make_unique<Physics::World>();
}

Core::~Core() {
  physics_world_.reset();
}

void Core::Start() {
  thread_start_time_ = std::chrono::steady_clock::now();
  logic_thread_ = std::thread(&Core::LogicThread, this);
}

void Core::Stop() {
  stop_logic_thread_ = true;
  logic_thread_.join();
}

void Core::LogicThread() {
  auto start_time = std::chrono::steady_clock::now();
  LAND_INFO("Thread time offset: {}",
            std::chrono::duration<float, std::chrono::seconds::period>(
                start_time - thread_start_time_)
                .count());
  while (!stop_logic_thread_) {
    Animation::CommandBuffer command_buffer;
    command_buffer.time_point = std::chrono::steady_clock::now();
    animation_manager->SetWorkingCommandBuffer(&command_buffer);

    std::lock_guard<std::mutex> lock(load_queue_mutex_);
    while (!load_queue_.empty()) {
      load_queue_.front()();
      load_queue_.pop();
    }

    UpdateSubordinates();

    animation_manager->SetWorkingCommandBuffer(nullptr);
    while (!animation_manager->ExecuteCommandBuffer(std::move(command_buffer),
                                                    stop_logic_thread_))
      ;
    metronome_.Tick();
  }

  Animation::CommandBuffer command_buffer;
  command_buffer.time_point = std::chrono::steady_clock::now();
  animation_manager->SetWorkingCommandBuffer(&command_buffer);
  std::set<Object *> release_modules = GetSubordinates();
  for (auto &module : release_modules) {
    delete module;
  }
  animation_manager->SetWorkingCommandBuffer(nullptr);
  animation_manager->ExecuteCommandBuffer(std::move(command_buffer), true);
}
}  // namespace GameX::Base
