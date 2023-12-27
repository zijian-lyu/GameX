#pragma once
#include "GameBall/core/utils.h"
#include "GameBall/logic/world.h"

namespace GameBall::Logic {

void EventRemovePlayer(World *world, uint64_t player_id);

void EventRemoveUnit(World *world, uint64_t unit_id);

void EventRemoveObstacle(World *world, uint64_t obstacle_id);

void EventCreatePlayer(World *world);

template <class UnitType, class... Args>
void EventCreateUnit(World *world, uint64_t player_id, Args &&...args) {
  world->PushEvent([world, player_id,
                    args = std::make_tuple(std::forward<Args>(args)...)]() {
    world->CreateUnit<UnitType>(player_id, args);
  });
}

template <class ObstacleType, class... Args>
void EventCreateObstacle(World *world, Args &&...args) {
  world->PushEvent(
      [world, args = std::make_tuple(std::forward<Args>(args)...)]() {
        world->CreateObstacle<ObstacleType>(args);
      });
}
}  // namespace GameBall::Logic
