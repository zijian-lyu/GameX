#pragma once
#include "GameX/animation/camera.h"

#include "GameX/animation/manager.h"

namespace GameX::Animation {
template <class... Args>
Camera::Camera(struct Scene *scene, Args &&...args): DynamicObject(scene->Manager()) {
    manager_->RecordCommand(
            [this, scene, args...]() {
            camera_ = std::make_unique<Base::Camera>(
                    scene->Handle(),
            args...);
            }
        );
}
}
