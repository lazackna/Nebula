//
// Created by Jasper on 1/19/2024.
//

#ifndef NEBULA_MAIN_LIGHTING_HPP
#define NEBULA_MAIN_LIGHTING_HPP

#include <glm/glm.hpp>

namespace nebula {
    struct Light {
        glm::vec3 Position;
        glm::vec3 Color;

        float Linear;
        float Quadratic;
        float Radius;
    };
}
#endif //NEBULA_MAIN_LIGHTING_HPP
