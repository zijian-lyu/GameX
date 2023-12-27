#pragma once

#include "GameBall/core/asset_manager.h"
#include "GameBall/core/utils.h"
#include "GameBall/logic/logic.h"

namespace GameBall {

typedef GameX::Base::ApplicationSettings GameSettings;

class GameBall : public GameX::Base::Application {
 public:
  GameBall(const GameSettings &settings);

  ~GameBall();

  void OnInit() override;

  void OnUpdate() override;

  void OnRender() override;

  void OnCleanup() override;

  class AssetManager *AssetManager() {
    return asset_manager_.get();
  }

  GameX::Graphics::PScene Scene() {
    return scene_.get();
  }

  template <class ActorType, class... Args>
  Actor *CreateActor(uint64_t object_id, Args &&...args) {
    auto actor = new ActorType(this, std::forward<Args>(args)...);
    actors_.insert({object_id, actor});
    return actors_.at(object_id);
  }

  Actor *GetActor(uint64_t object_id) {
    if (!actors_.count(object_id)) {
      return nullptr;
    }
    return actors_.at(object_id);
  }

 private:
  friend class Logic::Manager;

  GameX::Graphics::UScene scene_;
  GameX::Graphics::UFilm film_;
  uint64_t synced_world_version_ = 0;
  std::unique_ptr<Logic::Manager> logic_manager_;
  std::unique_ptr<class AssetManager> asset_manager_;
  std::map<uint64_t, Actor *> actors_;
  uint64_t synced_logic_world_version_{0};
};
}  // namespace GameBall
