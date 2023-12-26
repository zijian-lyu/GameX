#include "GameX/shaders/shaders.h"

namespace GameX::Graphics {
namespace {

#include "built_in_shaders.inl"

}

std::vector<uint32_t> BuiltInShaderSpv(const std::string &code_path) {
  auto code = GetShaderCode(code_path);
  return grassland::vulkan::CompileGLSLToSPIRV(
      code, grassland::vulkan::FileNameExtensionToShaderStage(code_path));
}
}  // namespace GameX::Graphics
