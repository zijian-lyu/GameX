#pragma once

#include "GameBall/core/actor.h"
#include "GameBall/core/actors/actors.h"
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

  virtual void UpdateTick();

  virtual void SyncState(GameBall *app) const = 0;

#define SYNC_ACTOR_FUNC_DECLARE(ActorTy)                      \
  typedef ActorTy ActorType;                                  \
                                                              \
  void SyncActorState(GameBall *app, ActorType *actor) const; \
                                                              \
  void SyncState(GameBall *app) const override;

  bool ActorInitialize() const;

 protected:
  World *world_{nullptr};

 private:
  friend World;
  bool actor_initialize_{true};
  uint64_t object_id_{};
};
}  // namespace Logic

#define SYNC_ACTOR_FUNC(ObjectType)                                            \
  void ObjectType::SyncState(GameBall *app) const {                            \
    auto actor = app->GetActor(ObjectId());                                    \
    if (!actor) {                                                              \
      actor = app->CreateActor<ObjectType::ActorType>(ObjectId());             \
    }                                                                          \
    ObjectType::ActorType *real_actor =                                        \
        dynamic_cast<ObjectType::ActorType *>(actor);                          \
    if (!real_actor) {                                                         \
      LAND_ERROR("Corresponding actor doesn't match requested type.");         \
    }                                                                          \
    SyncActorState(app, real_actor);                                           \
  }                                                                            \
                                                                               \
  void ObjectType::SyncActorState(GameBall *app, ObjectType::ActorType *actor) \
      const

}  // namespace GameBall
