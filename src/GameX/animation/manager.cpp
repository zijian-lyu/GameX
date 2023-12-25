#include "GameX/animation/manager.h"

namespace GameX::Animation {
Manager::Manager(Base::Renderer *renderer) : renderer_(renderer) {
  scene_ = std::make_unique<Base::Scene>(renderer_);
}

Manager::~Manager() {
  scene_.reset();
}

void Manager::Update(float delta_time) {
}

}  // namespace GameX::Animation
