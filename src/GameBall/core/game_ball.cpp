#include "GameBall/core/game_ball.h"

namespace GameBall {

GameBall::GameBall(const GameSettings &settings)
    : GameX::Base::Application(settings) {
  auto extent = FrameExtent();
  float aspect = static_cast<float>(extent.width) / extent.height;
  scene_ = Renderer()->CreateScene();
  film_ = Renderer()->CreateFilm(extent.width, extent.height);
  static_model_ = Renderer()->CreateStaticModel("models/sphere.obj");
  animated_model_ = Renderer()->CreateAnimatedModel("models/sphere.obj");
  static_entity_ = scene_->CreateEntity(static_model_.get());
  animated_entity_ = scene_->CreateEntity(animated_model_.get());
  camera_ = scene_->CreateCamera(glm::vec3{0.0f, 0.0f, 5.0f},
                                 glm::vec3{0.0f, 0.0f, 0.0f}, 45.0f, aspect,
                                 1.0f, 10.0f);
  ambient_light_ =
      scene_->CreateLight<GameX::Graphics::AmbientLight>(glm::vec3{0.3f});
  directional_light_ = scene_->CreateLight<GameX::Graphics::DirectionalLight>(
      glm::vec3{0.7f}, glm::vec3{1.0f, 1.0f, 1.0f});

  moon_texture_ = Renderer()->CreateImage("textures/2k_moon.jpg");
  static_entity_->SetAlbedoImage(moon_texture_.get());
}

GameBall::~GameBall() {
  ambient_light_.reset();
  camera_.reset();
  animated_entity_.reset();
  static_entity_.reset();
  animated_model_.reset();
  static_model_.reset();
  film_.reset();
}

void GameBall::OnInit() {
  for (auto &vertex : animated_model_->Vertices()) {
    vertex.color = (vertex.position + 1.0f) * 0.5f;
  }
  animated_model_->SyncMeshData();
}

void GameBall::OnUpdate() {
  static auto last_time = std::chrono::steady_clock::now();
  auto current_time = std::chrono::steady_clock::now();
  float delta_time = std::chrono::duration<float, std::chrono::seconds::period>(
                         current_time - last_time)
                         .count();
  last_time = current_time;
  static float omega = 0.0f;

  omega += glm::radians(90.0f) * delta_time;
  static_entity_->SetAffineMatrix(
      glm::translate(glm::mat4{1.0f}, glm::vec3{-0.5f, 0.0f, 0.0f}) *
      glm::rotate(glm::mat4(1.0f), omega, glm::vec3(1.0f, -1.0f, -1.0f)) *
      glm::scale(glm::mat4{1.0f}, glm::vec3{0.5f}));
  animated_entity_->SetAffineMatrix(
      glm::translate(glm::mat4{1.0f}, glm::vec3{0.5f, 0.0f, 0.0f}) *
      glm::rotate(glm::mat4(1.0f), omega, glm::vec3(1.0f, 1.0f, 1.0f)) *
      glm::scale(glm::mat4{1.0f}, glm::vec3{0.5f}));
}

void GameBall::OnRender() {
  auto cmd_buffer = VkCore()->CommandBuffer();
  Renderer()->RenderPipeline()->Render(cmd_buffer->Handle(), *scene_, *camera_,
                                       *film_);

  OutputImage(cmd_buffer->Handle(), film_->output_image.get());
}

void GameBall::OnCleanup() {
}
}  // namespace GameBall
