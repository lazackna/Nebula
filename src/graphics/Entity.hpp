//
// Created by Jasper on 2/13/2024.
//

#ifndef NEBULA_MAIN_ENTITY_HPP
#define NEBULA_MAIN_ENTITY_HPP

#include <glm/glm.hpp>
#include "mesh/Mesh.hpp"

namespace nebula {

    class Shader;

    class Entity {
        std::shared_ptr<Mesh> mesh;
    public:
        glm::mat4 model;

        explicit Entity(std::shared_ptr<Mesh> mesh);

        void draw(Shader& shader) const;
    };

} // nebula

#endif //NEBULA_MAIN_ENTITY_HPP
