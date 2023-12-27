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

  virtual void SyncState(GameBall *app) const = 0;

#define SYNC_ACTOR_FUNC_DECLARE(ActorTy)       \
  typedef ActorTy ActorType;                   \
  void SyncActorState(ActorType *actor) const; \
  void SyncState(GameBall *app) const override;

 protected:
  World *world_{nullptr};

 private:
  uint64_t object_id_{};
};
}  // namespace Logic

#define SYNC_ACTOR_FUNC(ObjectType)                                    \
  void ObjectType::SyncState(GameBall *app) const {                    \
    auto actor = app->GetActor(ObjectId());                            \
    if (!actor) {                                                      \
      actor = app->CreateActor<ObjectType::ActorType>(ObjectId());     \
    }                                                                  \
    ObjectType::ActorType *real_actor =                                \
        dynamic_cast<ObjectType::ActorType *>(actor);                  \
    if (!real_actor) {                                                 \
      LAND_ERROR("Corresponding actor doesn't match requested type."); \
    }                                                                  \
    SyncActorState(real_actor);                                        \
  }                                                                    \
  void ObjectType::SyncActorState(ObjectType::ActorType *actor) const

}  // namespace GameBall
