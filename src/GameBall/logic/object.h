#pragma once

#include "GameBall/core/actor.h"
#include "GameBall/core/utils.h"

namespace GameBall {
class GameBall;
namespace Logic {
class World;

class Object {
 public:
  Object(World *world);

  virtual ~Object();

  uint64_t ObjectId() const;

  virtual void UpdateTick() const;

  void SyncState(GameBall *app) const;

  virtual void SyncActorState(Actor *actor) = 0;

#define SYNC_ACTOR_FUNC_DECLARE(ActorType)                    \
  void SyncActorState(ActorType *actor);                      \
  void SyncActorState(Actor *actor) override {                \
    ActorType *real_actor = dynamic_cast<ActorType *>(actor); \
    SyncActorState(real_actor);                               \
  }

 protected:
  World *world_{nullptr};

 private:
  uint64_t object_id_{};
};
}  // namespace Logic
}  // namespace GameBall
