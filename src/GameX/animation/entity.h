#pragma once
#include "GameX/animation/dynamic_object.h"
#include "GameX/animation/model.h"
#include "GameX/renderer/entity.h"

namespace GameX::Animation {
class Entity : public DynamicObject {
 public:
  typedef Base::Entity::EntitySettings EntitySettings;
  Entity(class Scene *scene, Model *model);
  virtual ~Entity();
  void Update(float delta_time) override;
  void SetEntitySettings(const EntitySettings &settings);

 private:
  std::unique_ptr<Base::Entity> entity_;
};
}  // namespace GameX::Animation
