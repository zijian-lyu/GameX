#version 450

layout(binding = 0, set = 0) uniform CameraData {
  mat4 view;
  mat4 proj;
}
camera_data;

const vec2[6] positions = vec2[6](vec2(-1.0, -1.0),
                                  vec2(1.0, -1.0),
                                  vec2(-1.0, 1.0),
                                  vec2(-1.0, 1.0),
                                  vec2(1.0, -1.0),
                                  vec2(1.0, 1.0));

layout(location = 0) out vec3 ray_direction;

void main() {
  gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
  ray_direction =
      normalize((gl_Position * vec4(1.0, -1.0, 0.0, 1.0)) * camera_data.proj)
          .xyz *
      mat3(camera_data.view);
}
