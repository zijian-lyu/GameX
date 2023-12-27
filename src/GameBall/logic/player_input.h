#pragma once
#include "GameBall/core/utils.h"

namespace GameBall::Logic {
struct PlayerInput {
  bool move_forward{false};
  bool move_backward{false};
  bool move_left{false};
  bool move_right{false};
  glm::vec3 orientation{0.0f, 0.0f, 1.0f};
};
}  // namespace GameBall::Logic
