#pragma once

#include "GameX/animation/command_buffer.h"
#include "GameX/animation/dynamic_object.h"
#include "GameX/animation/mesh.h"
#include "GameX/animation/model.h"
#include "GameX/animation/object.h"
#include "GameX/animation/scene.h"
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

  void RecordCommand(const std::function<void()> &command);

  void ExecuteCommandBuffer(CommandBuffer &&cmd_buffer) {
    std::lock_guard<std::mutex> lock(cmd_buffer_queue_mutex_);
    cmd_buffer_queue_.push(std::move(cmd_buffer));
  }

  void RegisterDynamicObject(DynamicObject *object);

  void UnregisterObject(Object *object);

  void UnregisterDynamicObject(DynamicObject *object);

  bool Render(VkCommandBuffer cmd_buffer);

  Base::Renderer *Renderer() const {
    return renderer_;
  }

  template <class... Args>
  [[nodiscard]] class Scene *CreateScene(Args &&...args) {
    return new class Scene(this, std::forward<Args>(args)...);
  }

  template <class... Args>
  [[nodiscard]] class Mesh *CreateMesh(Args &&...args) {
    return new class Mesh(this, std::forward<Args>(args)...);
  }

  template <class... Args>
  [[nodiscard]] class StaticModel *CreateStaticModel(Args &&...args) {
    return new class StaticModel(this, std::forward<Args>(args)...);
  }

  template <class... Args>
  [[nodiscard]] class DynamicModel *CreateDynamicModel(Args &&...args) {
    return new class DynamicModel(this, std::forward<Args>(args)...);
  }

  void SetPrimarySceneCamera(Scene *scene, Camera *camera);

  const Base::RenderPipeline::Film *PrimaryFilm() const {
    return film_.get();
  }

 private:
  void ProcessCommandBufferQueue();

  Base::Renderer *renderer_;
  std::unique_ptr<Base::RenderPipeline::Film> film_;

  std::set<DynamicObject *> dynamic_objects_;

  CommandBuffer *working_cmd_buffer_{};

  std::mutex cmd_buffer_queue_mutex_;
  std::queue<CommandBuffer> cmd_buffer_queue_;

  Scene *primary_scene_{};
  Camera *primary_camera_{};
};
}  // namespace GameX::Animation
