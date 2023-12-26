#include "GameBall/main/world.h"

namespace GameBall {

World::World(GameX::Base::Core *core) : Module(core) {
  LAND_INFO("Game world created...");
  scene_ = core_->AnimationManager()->CreateScene();
  auto extent = core_->AnimationManager()
                    ->Renderer()
                    ->App()
                    ->VkCore()
                    ->SwapChain()
                    ->Extent();
  auto aspect =
      static_cast<float>(extent.width) / static_cast<float>(extent.height);
  camera_ = scene_->CreateCamera(glm::vec3{0.0f, 0.0f, 3.0f},
                                 glm::vec3{0.0f, 0.0f, 0.0f}, 45.0f, aspect,
                                 0.1f, 100.0f);
  cube_ = core_->AnimationManager()->CreateMesh("models/sphere.obj");
  static_model_ = core_->AnimationManager()->CreateStaticModel(cube_);
  dynamic_model_ = core_->AnimationManager()->CreateDynamicModel(cube_);
  static_entity_ = scene_->CreateEntity(static_model_);
  dynamic_entity_ = scene_->CreateEntity(dynamic_model_);

  GameX::Animation::AmbientLight::AmbientLightData ambient_light_data{
      {1.0f, 1.0f, 1.0f}, 0.5f};
  ambient_light_ = scene_->CreateAmbientLight(ambient_light_data);

  GameX::Animation::DirectionalLight::DirectionalLightData
      directional_light_data{{1.0f, 1.0f, 1.0f},
                             0.5f,
                             glm::normalize(glm::vec3{1.0f, 1.0f, 1.0f})};
  directional_light_ = scene_->CreateDirectionalLight(directional_light_data);

  for (auto &vertex : cube_->Vertices()) {
    vertex.color = vertex.position + 0.5f;
  }
  dynamic_model_->SyncMeshData();

  core_->AnimationManager()->SetPrimarySceneCamera(scene_, camera_);

  dynamic_entity_->SetScale(glm::vec3{0.5f});
  static_entity_->SetScale(glm::vec3{0.5f});
}

World::~World() {
  ambient_light_->Release();
  directional_light_->Release();
  static_entity_->Release();
  dynamic_entity_->Release();
  static_model_->Release();
  dynamic_model_->Release();
  cube_->Release();
  camera_->Release();
  scene_->Release();
  LAND_INFO("Game world released...");
}

void World::Update() {
  static float omega = 0.0f;
  static_entity_->SetMotion(
      glm::vec3{-0.5f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
      glm::vec3{0.0f, 0.0f, 0.0f},
      glm::mat3{
          glm::rotate(glm::mat4{1.0f}, omega, glm::vec3{1.0f, -1.0f, -1.0f})},
      glm::vec3{1.0f, -1.0f, -1.0f}, glm::radians(180.0f));
  dynamic_entity_->SetMotion(
      glm::vec3{0.5f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
      glm::vec3{0.0f, 0.0f, 0.0f},
      glm::mat3{
          glm::rotate(glm::mat4{1.0f}, omega, glm::vec3{1.0f, 1.0f, 1.0f})},
      glm::vec3{1.0f, 1.0f, 1.0f}, glm::radians(180.0f));
  omega += glm::radians(180.0f) / 64.0f;
}

}  // namespace GameBall
