//
// Created by Jasper on 2/13/2024.
//

#ifndef NEBULA_MAIN_DEFERREDRENDERER_HPP
#define NEBULA_MAIN_DEFERREDRENDERER_HPP

#include "../Renderer.hpp"
#include "../../../shaders/BasicShader.hpp"
#include "../../buffersObjects/GBuffer.hpp"

namespace nebula {

    class DeferredRenderer : public Renderer{
        std::unique_ptr<GBuffer> gBuffer;

        std::shared_ptr<BasicShader> simpleShader;
    public:
        DeferredRenderer(unsigned int width, unsigned int height);

        void render(const std::vector<Entity> &entities, FpsCam &camera, const glm::mat4 &projection) override;
        //void render(const std::vector<Entity>& entities, FpsCam& camera, const glm::mat4& projection) override;
    };

} // nebula

#endif //NEBULA_MAIN_DEFERREDRENDERER_HPP
