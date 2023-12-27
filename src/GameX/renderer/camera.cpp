#include "GameX/renderer/camera.h"

#include "GameX/application/application.h"
#include "GameX/renderer/renderer.h"

namespace GameX::Graphics {

Camera::Camera(Scene *scene,
               const glm::vec3 eye,
               const glm::vec3 center,
               const float fovY,
               const float aspect,
               const float near_z,
               const float far_z) {
  Init(scene, eye, center, fovY, aspect, near_z, far_z);
}

void Camera::Init(Scene *scene,
                  const glm::vec3 eye,
                  const glm::vec3 center,
                  const float fovY,
                  const float aspect,
                  const float near_z,
                  const float far_z) {
  scene_ = scene;
  camera_buffer_ =
      std::make_unique<grassland::vulkan::DynamicBuffer<CameraData>>(
          scene->Renderer()->App()->VkCore(), 1,
          VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);

  camera_buffer_->At(0).view_matrix_ = glm::lookAt(eye, center, {0, 1, 0});
  camera_buffer_->At(0).projection_matrix_ =
      glm::perspectiveZO(glm::radians(fovY), aspect, near_z, far_z);

  descriptor_sets_.resize(
      scene->Renderer()->App()->VkCore()->MaxFramesInFlight());
  for (size_t i = 0; i < descriptor_sets_.size(); ++i) {
    descriptor_sets_[i] = std::make_unique<grassland::vulkan::DescriptorSet>(
        scene->Renderer()->App()->VkCore(), scene->DescriptorPool(),
        CameraDescriptorSetLayout(scene->Renderer()));

    VkDescriptorBufferInfo buffer_info = {};
    buffer_info.buffer = camera_buffer_->GetBuffer(i)->Handle();
    buffer_info.offset = 0;
    buffer_info.range = sizeof(CameraData);

    VkWriteDescriptorSet write_descriptor_set = {};
    write_descriptor_set.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_descriptor_set.dstSet = descriptor_sets_[i]->Handle();
    write_descriptor_set.dstBinding = 0;
    write_descriptor_set.dstArrayElement = 0;
    write_descriptor_set.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    write_descriptor_set.descriptorCount = 1;
    write_descriptor_set.pBufferInfo = &buffer_info;

    vkUpdateDescriptorSets(
        scene->Renderer()->App()->VkCore()->Device()->Handle(), 1,
        &write_descriptor_set, 0, nullptr);
  }

  scene_->Renderer()->RegisterSyncObject(camera_buffer_.get());
}

Camera::~Camera() {
  scene_->DestroyCamera(this);
  scene_->Renderer()->UnregisterSyncObject(camera_buffer_.get());
}

grassland::vulkan::DescriptorSetLayout *CameraDescriptorSetLayout(
    Renderer *renderer) {
  static std::map<Renderer *, grassland::vulkan::DescriptorSetLayout *>
      camera_descriptor_set_layouts;
  if (!camera_descriptor_set_layouts.count(renderer)) {
    grassland::vulkan::DescriptorSetLayout *&camera_descriptor_set_layout =
        camera_descriptor_set_layouts[renderer];
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    bindings.resize(1);
    bindings[0].binding = 0;
    bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    bindings[0].descriptorCount = 1;
    bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    bindings[0].pImmutableSamplers = nullptr;

    camera_descriptor_set_layout = new grassland::vulkan::DescriptorSetLayout(
        renderer->App()->VkCore(), bindings);
    renderer->AddReleaseCallback([camera_descriptor_set_layout]() {
      delete camera_descriptor_set_layout;
    });
    return camera_descriptor_set_layout;
  }
  return camera_descriptor_set_layouts.at(renderer);
}
}  // namespace GameX::Graphics
