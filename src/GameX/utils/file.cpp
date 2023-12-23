#include "GameX/utils/file.h"

namespace GameX {

bool FileExists(const std::string &path) {
  struct stat buffer;
  return (stat(path.c_str(), &buffer) == 0);
}
}  // namespace GameX
