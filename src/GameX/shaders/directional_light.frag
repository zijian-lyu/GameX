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

layout(std140, set = 1, binding = 0) uniform DirectionalLight {
  vec3 color;
  float intensity;
  vec3 direction;
}
directional_light;

layout(location = 0) out vec4 output_color;

void main() {
  float NdotL = max(dot(normalize(subpassLoad(normal_input).rgb),
                        directional_light.direction),
                    0.0);
  if (NdotL < 1e-3) {
    discard;
  }
  output_color = vec4(NdotL * subpassLoad(albedo_input).rgb *
                          directional_light.color * directional_light.intensity,
                      1.0);
}
