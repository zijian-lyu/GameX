#include "GameBall/main/world.h"

namespace GameBall {

World::World(GameX::Base::Core *core) : Module(core) {
  LAND_INFO("Game world created...");
  scene_ = core->AnimationManager()->CreateScene();
}

World::~World() {
  scene_->Release();
  LAND_INFO("Game world released...");
}

void World::Update() {
  ;
}

}  // namespace GameBall
