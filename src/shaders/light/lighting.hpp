//
// Created by Jasper on 1/19/2024.
//

#ifndef NEBULA_MAIN_LIGHTING_HPP
#define NEBULA_MAIN_LIGHTING_HPP

#include <glm/glm.hpp>

namespace nebula {
    struct PointLight {
        //is direction when w == 0.
        //Point light when w == 1.
        glm::vec4 direction;

        glm::vec3 color;
        float ambientIntensity;
        float diffuseIntensity;
    };
}
#endif //NEBULA_MAIN_LIGHTING_HPP
