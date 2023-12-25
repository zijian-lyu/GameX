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
  logic_thread = std::thread(&Core::LogicThread, this);
}

void Core::Stop() {
  stop_logic_thread = true;
  logic_thread.join();
}

void Core::LogicThread() {
  auto start = std::chrono::steady_clock::now();
  while (!stop_logic_thread) {
    Animation::CommandBuffer command_buffer;
    animation_manager->SetWorkingCommandBuffer(&command_buffer);

    UpdateSubordinates();

    animation_manager->SetWorkingCommandBuffer(nullptr);
    animation_manager->ExecuteCommandBuffer(std::move(command_buffer));
    metronome_.Tick();
  }
}
}  // namespace GameX::Base
