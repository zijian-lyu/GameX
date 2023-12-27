#include "GameBall/core/game_ball.h"

#include <queue>

#include "GameBall/core/actors/actors.h"
#include "GameBall/logic/obstacles/obstacles.h"
#include "GameBall/logic/units/units.h"

namespace GameBall {

GameBall::GameBall(const GameSettings &settings)
    : GameX::Base::Application(settings) {
  auto extent = FrameExtent();
  float aspect = static_cast<float>(extent.width) / extent.height;
  scene_ = Renderer()->CreateScene();
  film_ = Renderer()->CreateFilm(extent.width, extent.height);
  logic_manager_ = std::make_unique<Logic::Manager>();
  asset_manager_ = std::make_unique<class AssetManager>(Renderer());
}

GameBall::~GameBall() {
  asset_manager_.reset();
}

void GameBall::OnInit() {
  auto world = logic_manager_->World();

  scene_->SetEnvmapImage(asset_manager_->ImageFile("textures/envmap.hdr"));

  ambient_light_ = scene_->CreateLight<GameX::Graphics::AmbientLight>();
  ambient_light_->SetLight(glm::vec3{0.3});

  auto primary_player = world->CreatePlayer();
  auto primary_obstacle = world->CreateObstacle<Logic::Obstacles::Block>(
      glm::vec3{0.0f, 0.0f, 0.0f}, 1.0f, false, glm::vec3{1.0f, 1.0f, 1.0f});

  VkExtent2D extent = FrameExtent();
  float aspect = static_cast<float>(extent.width) / extent.height;
  camera_ = scene_->CreateCamera(glm::vec3{0.0f, 10.0f, 10.0f},
                                 glm::vec3{0.0f, 0.0f, 0.0f}, 45.0f, aspect,
                                 0.1f, 100.0f);

  logic_manager_->Start();
}

void GameBall::OnCleanup() {
  logic_manager_->Stop();
  std::queue<Actor *> actors_to_remove;
  for (auto &actor : actors_) {
    actors_to_remove.push(actor.second);
  }

  while (!actors_to_remove.empty()) {
    auto actor = actors_to_remove.front();
    actors_to_remove.pop();
    actors_.erase(actor->SyncedLogicWorldVersion());
    delete actor;
  }
}

void GameBall::OnUpdate() {
  static auto last_time = std::chrono::steady_clock::now();
  auto current_time = std::chrono::steady_clock::now();
  float delta_time = std::chrono::duration<float, std::chrono::seconds::period>(
                         current_time - last_time)
                         .count();
  last_time = current_time;

  {
    std::lock_guard<std::mutex> lock(logic_manager_->logic_mutex_);
    logic_manager_->world_->SyncWorldState(this);
  }

  std::queue<Actor *> actors_to_remove;
  for (auto &actor : actors_) {
    if (actor.second->SyncedLogicWorldVersion() ==
        synced_logic_world_version_) {
      actor.second->Update(delta_time);
    } else {
      actors_to_remove.push(actor.second);
    }
  }

  while (!actors_to_remove.empty()) {
    auto actor = actors_to_remove.front();
    actors_to_remove.pop();
    actors_.erase(actor->SyncedLogicWorldVersion());
    delete actor;
  }
}

void GameBall::OnRender() {
  auto cmd_buffer = VkCore()->CommandBuffer();
  Renderer()->RenderPipeline()->Render(cmd_buffer->Handle(), *scene_, *camera_,
                                       *film_);

  OutputImage(cmd_buffer->Handle(), film_->output_image.get());
}
}  // namespace GameBall
