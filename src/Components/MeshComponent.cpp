//
// Created by Jasper on 2/1/2024.
//

#include "MeshComponent.hpp"

namespace nebula {
    MeshComponent::MeshComponent(const std::shared_ptr<Mesh> &mesh) : mesh(mesh) {}

    const std::shared_ptr<Mesh> &MeshComponent::getMesh() const {
        return mesh;
    }
} // nebula