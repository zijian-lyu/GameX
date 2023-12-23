#version 450

layout(location = 0) in vec3 position;

layout(binding = 0, set = 0) uniform CameraData {
  mat4 view;
  mat4 proj;
}
camera_data;

layout(binding = 0, set = 1) uniform EntityData {
  mat4 model;
}
transform_data;

void main() {
}
