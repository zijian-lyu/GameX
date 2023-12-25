#include "GameBall/main/world.h"

namespace GameBall {

World::World(GameX::Base::Core *core) : Module(core) {
  LAND_INFO("Game world created...");
  scene_ = core->AnimationManager()->CreateScene();
  camera_ = scene_->CreateCamera(glm::vec3{0.0f, 0.0f, 3.0f},
                                 glm::vec3{0.0f, 0.0f, 0.0f}, 45.0f, 1.0f, 0.1f,
                                 100.0f);
  core->AnimationManager()->SetPrimarySceneCamera(scene_, camera_);
  cube_ = core->AnimationManager()->CreateMesh("models/cube.obj");
  static_model_ = core->AnimationManager()->CreateStaticModel(cube_);
  dynamic_model_ = core->AnimationManager()->CreateDynamicModel(cube_);

  for (auto &vertex : cube_->Vertices()) {
    vertex.color = vertex.position + 0.5f;
  }
  dynamic_model_->SyncMeshData();
}

World::~World() {
  static_model_->Release();
  dynamic_model_->Release();
  cube_->Release();
  camera_->Release();
  scene_->Release();
  LAND_INFO("Game world released...");
}

void World::Update() {
  ;
}

}  // namespace GameBall
