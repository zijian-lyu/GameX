#include "GameBall/main/world.h"

namespace GameBall {

World::World(GameX::Base::Core *core) : Module(core) {
  LAND_INFO("Game world created...");
}

World::~World() {
  LAND_INFO("Game world released...");
}

void World::Update() {
  //        static int frame_count = 0;
  //        LAND_INFO("Frame: {} Dur: {}", frame_count,
  //        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()
  //        - start_time).count()); frame_count++;
}

}  // namespace GameBall
