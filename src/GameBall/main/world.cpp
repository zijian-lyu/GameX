#include "GameBall/main/world.h"

namespace GameBall {

World::World(GameX::Base::Core *core) : Module(core) {
  LAND_INFO("Game world created...");
}

World::~World() {
  LAND_INFO("Game world released...");
}

void World::Update() {
  ;
}

}  // namespace GameBall
