#include "GameBall/core/game_ball.h"

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
  logic_manager_->Start();
}

void GameBall::OnCleanup() {
  logic_manager_->Stop();
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
  };
}

void GameBall::OnRender() {
  auto cmd_buffer = VkCore()->CommandBuffer();
  //  Renderer()->RenderPipeline()->Render(cmd_buffer->Handle(), *scene_,
  //  *camera_,
  //                                       *film_);
  //
  //  OutputImage(cmd_buffer->Handle(), film_->output_image.get());
}
}  // namespace GameBall
