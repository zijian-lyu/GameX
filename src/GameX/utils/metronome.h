#pragma once
#include <chrono>

namespace GameX::Base {
class Metronome {
 public:
  Metronome(std::chrono::duration<long long int, std::ratio<1, 1000000>> dur =
                std::chrono::microseconds(15625));  // 1/64 second

  void Tick();

 private:
  std::chrono::duration<long long int, std::ratio<1, 1000000>> dur_;
  std::chrono::time_point<std::chrono::steady_clock> last_time_{};
};
}  // namespace GameX::Base
