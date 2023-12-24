#version 450

layout(input_attachment_index = 0,
       set = 0,
       binding = 0) uniform subpassInput albedo_input;
layout(input_attachment_index = 1,
       set = 0,
       binding = 1) uniform subpassInput normal_input;
layout(input_attachment_index = 2,
       set = 0,
       binding = 2) uniform subpassInput position_input;

layout(std140, set = 1, binding = 0) uniform AmbientLight {
  vec3 color;
  float intensity;
}
ambient_light;

layout(location = 0) out vec4 output_color;

void main() {
  output_color = vec4(subpassLoad(albedo_input).rgb * ambient_light.color *
                          ambient_light.intensity,
                      1.0);
}
