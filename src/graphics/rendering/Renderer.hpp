//
// Created by Jasper on 2/13/2024.
//

#ifndef NEBULA_MAIN_RENDERER_HPP
#define NEBULA_MAIN_RENDERER_HPP

#include <vector>
#include "../Entity.hpp"

#include "../FpsCam.hpp"

namespace nebula {

    class Renderer {
    public:
        virtual ~Renderer() = default;

        virtual void render(const std::vector<Entity>& entities, FpsCam& camera, const glm::mat4& projection) = 0;
    };

} // nebula

#endif //NEBULA_MAIN_RENDERER_HPP
