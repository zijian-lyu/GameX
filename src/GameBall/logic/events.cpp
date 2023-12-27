#include "GameBall/logic/events.h"

namespace GameBall::Logic {

void EventRemovePlayer(World *world, uint64_t player_id) {
  world->PushEvent([world, player_id]() { world->RemovePlayer(player_id); });
}

void EventRemoveUnit(World *world, uint64_t unit_id) {
  world->PushEvent([world, unit_id]() { world->RemoveUnit(unit_id); });
}

void EventRemoveObstacle(World *world, uint64_t obstacle_id) {
  world->PushEvent(
      [world, obstacle_id]() { world->RemoveObstacle(obstacle_id); });
}

void EventCreatePlayer(World *world) {
  world->PushEvent([world]() { world->CreatePlayer(); });
}
}  // namespace GameBall::Logic
