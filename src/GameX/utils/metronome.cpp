#include "GameX/utils/metronome.h"

#include <thread>

namespace GameX::Base {
Metronome::Metronome(
    std::chrono::duration<long long int, std::ratio<1, 1000000>> dur)
    : dur_(dur), last_time_(std::chrono::steady_clock::now()) {
}

void Metronome::Tick() {
  auto resume_time = last_time_ + dur_;
  auto current_time = std::chrono::steady_clock::now();
  if (current_time < resume_time) {
    std::this_thread::sleep_until(resume_time);
    last_time_ = resume_time;
  } else {
    last_time_ = current_time;
  }
}
}  // namespace GameX::Base
