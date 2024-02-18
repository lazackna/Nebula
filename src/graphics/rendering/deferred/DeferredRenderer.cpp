//
// Created by Jasper on 2/13/2024.
//

#include "DeferredRenderer.hpp"
#include "../../FpsCam.hpp"

namespace nebula {

    DeferredRenderer::DeferredRenderer(unsigned int width, unsigned int height) : Renderer() {
        gBuffer = std::make_unique<GBuffer>(width, height);

        simpleShader = std::make_shared<BasicShader>("resources/simple");
    }

    void DeferredRenderer::render(const std::vector<Entity> &entities, FpsCam &camera, const glm::mat4 &projection) {
        simpleShader->use();
        simpleShader->setViewMatrix(camera.getMatrix());
        simpleShader->setProjectionMatrix(projection);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0., 0., 0., 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (const auto &item: entities) {
            item.draw(*simpleShader);
        }
    }
} // nebula