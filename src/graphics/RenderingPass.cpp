//
// Created by User on 2/7/2024.
//

#include "RenderingPass.hpp"

namespace nebula {
    RenderingPass::RenderingPass(const Fbo &fbo, Shader &shader, const std::string& name) : fbo(fbo), texture(fbo, GL_RGBA16F, GL_RGB, GL_FLOAT, GL_COLOR_ATTACHMENT0) ,shader(shader) {
        texture.name = name;
    }

    void RenderingPass::render(FpsCam &camera, const glm::mat4 &model, const glm::mat4 &projection, Mesh &mesh) {
        shader.use();
        shader.setProjectionMatrix(projection);
        shader.setViewMatrix(camera.getMatrix());
        shader.setModelMatrix(model);

        fbo->bind();
        glEnable(GL_DEPTH_TEST);
        glClearColor(0., 0., 0., 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mesh.draw(shader);

        fbo->unbind();
    }

    Texture &RenderingPass::getTexture() {
        return texture;
    }
} // nebula