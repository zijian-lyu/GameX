#include "GameX/animation/entity.h"

#include "GameX/animation/manager.h"

namespace GameX::Animation {
Entity::~Entity() {
}

void Entity::Update(float delta_time) {
}

Entity::Entity(struct Scene *scene, Model *model)
    : DynamicObject(scene->Manager()) {
  manager_->RecordCommand([this, scene, model]() {
    entity_ = scene->Handle()->CreateEntity(model->Handle());
  });
}

void Entity::SetEntitySettings(const Entity::EntitySettings &settings) {
  manager_->RecordCommand(
      [this, settings]() { entity_->SetEntitySettings(settings); });
}
}  // namespace GameX::Animation
