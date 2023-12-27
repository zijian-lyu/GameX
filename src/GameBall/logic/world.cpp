#include "GameBall/logic/world.h"

namespace GameBall::Logic {

World::World() {
}

World::~World() {
}

GameX::Physics::World *World::PhysicsWorld() const {
  return physics_world_.get();
}

uint64_t World::RegisterObject(Object *object) {
  object_map_.insert(std::make_pair(next_object_id_, object));
  return next_object_id_++;
}

void World::UnregisterObject(uint64_t object_id) {
  object_map_.erase(object_id);
}

uint64_t World::RegisterUnit(Unit *unit) {
  unit_map_.insert(std::make_pair(next_unit_id_, unit));
  return next_unit_id_++;
}

void World::UnregisterUnit(uint64_t unit_id) {
  unit_map_.erase(unit_id);
}

uint64_t World::RegisterObstacle(Obstacle *obstacle) {
  obstacle_map_.insert(std::make_pair(next_obstacle_id_, obstacle));
  return next_obstacle_id_++;
}

void World::UnregisterObstacle(uint64_t obstacle_id) {
  obstacle_map_.erase(obstacle_id);
}

uint64_t World::RegisterPlayer(Player *player) {
  player_map_.insert(std::make_pair(next_player_id_, player));
  return next_player_id_++;
}

void World::UnregisterPlayer(uint64_t player_id) {
  player_map_.erase(player_id);
}

void World::UpdateTick() {
  LAND_INFO("Update Tick... {}", world_version_);
  world_version_++;
}
}  // namespace GameBall::Logic
