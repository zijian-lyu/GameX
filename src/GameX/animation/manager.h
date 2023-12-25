#pragma once

#include "GameX/animation/command_buffer.h"
#include "GameX/animation/dynamic_object.h"
#include "GameX/animation/object.h"
#include "GameX/renderer/renderer.h"

namespace GameX::Animation {
class Manager {
 public:
  Manager(Base::Renderer *renderer);

  ~Manager();

  void Update(float delta_time);

  void SetWorkingCommandBuffer(CommandBuffer *cmd_buffer) {
    working_cmd_buffer_ = cmd_buffer;
  }

  void PushCommand(const std::function<void(Manager *)> &command);

  void ExecuteCommandBuffer(CommandBuffer &&cmd_buffer) {
    std::lock_guard<std::mutex> lock(cmd_buffer_queue_mutex_);
    cmd_buffer_queue_.push(std::move(cmd_buffer));
  }

  void RegisterObject(Object *object);

  void RegisterDynamicObject(DynamicObject *object);

  void UnregisterObject(Object *object);

  void UnregisterDynamicObject(DynamicObject *object);

 private:
  void ProcessCommandBufferQueue();

  Base::Renderer *renderer_;
  std::unique_ptr<Base::Scene> scene_;
  std::unique_ptr<Base::RenderPipeline::Film> film_;

  std::set<Object *> objects_;
  std::set<DynamicObject *> dynamic_objects_;

  CommandBuffer *working_cmd_buffer_{};

  std::mutex cmd_buffer_queue_mutex_;
  std::queue<CommandBuffer> cmd_buffer_queue_;
};
}  // namespace GameX::Animation
