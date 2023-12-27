#pragma once
#include "GameBall/core/utils.h"
#include "GameBall/logic/object.h"
#include "GameBall/logic/obstacle.h"
#include "GameBall/logic/player.h"
#include "GameBall/logic/unit.h"

namespace GameBall::Logic {
class Manager;
class Object;
class Unit;
class Obstacle;
class Player;
class World {
 public:
  World();
  ~World();
  GameX::Physics::World *PhysicsWorld() const;

  uint64_t RegisterObject(Object *object);
  void UnregisterObject(uint64_t object_id);

  uint64_t RegisterUnit(Unit *unit);
  void UnregisterUnit(uint64_t unit_id);

  uint64_t RegisterObstacle(Obstacle *obstacle);
  void UnregisterObstacle(uint64_t obstacle_id);

  uint64_t RegisterPlayer(Player *player);
  void UnregisterPlayer(uint64_t player_id);

  uint64_t Version() const {
    return world_version_;
  }

 private:
  friend ::GameBall::GameBall;
  friend ::GameBall::Logic::Manager;
  void UpdateTick();
  std::unique_ptr<GameX::Physics::World> physics_world_;
  uint64_t next_object_id_{1};
  std::map<uint64_t, Object *> object_map_;

  uint64_t next_unit_id_{1};
  std::map<uint64_t, Unit *> unit_map_;

  uint64_t next_obstacle_id_{1};
  std::map<uint64_t, Obstacle *> obstacle_map_;

  uint64_t next_player_id_{1};
  std::map<uint64_t, Player *> player_map_;

  uint64_t world_version_{1};
};
}  // namespace GameBall::Logic
