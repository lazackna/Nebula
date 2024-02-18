//
// Created by Jasper on 2/13/2024.
//

#include "Entity.hpp"

#include <utility>

#include "../shaders/Shader.hpp"

namespace nebula {
    Entity::Entity(std::shared_ptr<Mesh> mesh) : mesh(std::move(mesh)), model(1.0f) {

    }

    void Entity::draw(Shader &shader) const{
        shader.setModelMatrix(model);

        mesh->draw(shader);
    }
} // nebula