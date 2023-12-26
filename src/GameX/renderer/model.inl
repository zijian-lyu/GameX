#pragma once
#include "GameX/renderer/model.h"
#include "GameX/renderer/renderer.h"
#include "GameX/application/application.h"

namespace GameX::Graphics {
    template<class... Args>
    AnimatedModel::AnimatedModel(Renderer *renderer, Args &&... args):Model(renderer) {
        mesh_ = new Base::Mesh(std::forward<Args>(args)...);

        vertex_buffer_.Init(renderer_->App()->VkCore(), mesh_->Vertices().size());
        vertex_buffer_.UploadContents(mesh_->Vertices().data(),
                                      mesh_->Vertices().size());
        index_buffer_.Init(renderer_->App()->VkCore(), mesh_->Indices().size());
        index_buffer_.UploadContents(mesh_->Indices().data(), mesh_->Indices().size());

        renderer_->RegisterSyncObject(&vertex_buffer_);
    }
}
