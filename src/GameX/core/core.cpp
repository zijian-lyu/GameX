#include "GameX/core/core.h"

namespace GameX::Base {

Core::Core(Animation::Manager *animation_manager)
    : animation_manager(animation_manager) {
}

Core::~Core() {
}

void Core::Start() {
}

void Core::Stop() {
}

void Core::LogicThread() {
}
}  // namespace GameX::Base
