#version 450

layout(location = 0) in vec3 ray_direction;

layout(set = 1, binding = 0) uniform EnvmapData {
  float envmap_rotation;
  float exposure;
}
envmap_data;

layout(set = 1, binding = 1) uniform sampler2D envmap;

layout(location = 0) out vec4 out_color;

void main() {
  vec3 direction = ray_direction;
  direction.yz = direction.yz * mat2(cos(envmap_data.envmap_rotation),
                                     sin(envmap_data.envmap_rotation),
                                     -sin(envmap_data.envmap_rotation),
                                     cos(envmap_data.envmap_rotation));
  vec3 color = textureLod(envmap, direction.xy * 0.5 + 0.5, 0).rgb;
  color = color * envmap_data.exposure;
  out_color = vec4(color, 1.0);
}
