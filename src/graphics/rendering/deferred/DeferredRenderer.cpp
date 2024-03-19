//
// Created by Jasper on 2/13/2024.
//

#include "DeferredRenderer.hpp"

#include "../../../ui/UIElements/TextureElement.hpp"
#include "../../../util/RandomUtils.hpp"

namespace nebula {

    DeferredRenderer::DeferredRenderer(unsigned int width, unsigned int height, const std::unique_ptr<Window> &window)
            : Renderer() {
        gBuffer = std::make_unique<GBuffer>(width, height);

        positionBuffer = FBO::create(width, height);
        positionRbo = RBO::create(positionBuffer, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
        positionShader = std::make_unique<BasicShader>("resources/testing/positions");
        positionPass = std::make_unique<RenderingPass>(positionBuffer, *positionShader, "position");

        normalBuffer = FBO::create(width, height);
        normalRbo = RBO::create(normalBuffer, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
        normalShader = std::make_unique<BasicShader>("resources/testing/normals");
        normalPass = std::make_unique<RenderingPass>(normalBuffer, *normalShader, "normal");

        colorBuffer = FBO::create(width, height);
        colorRbo = RBO::create(colorBuffer, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
        colorShader = std::make_unique<BasicShader>("resources/testing/colors");
        colorPass = std::make_unique<RenderingPass>(colorBuffer, *colorShader, "color");

        outputShader = std::make_unique<BasicShader>("resources/testing/shading");
        lightShader = std::make_unique<BasicShader>("resources/testing/lights");

        uiSystem = std::make_unique<UISystem>(window, "#version 400");
        UILayer debugLayer = UILayer("Texture Debugger");
        debugLayer.addElement(
                std::make_unique<TextureElement>(positionPass->getTexture(), width / 4, height / 4));
        debugLayer.addElement(
                std::make_unique<TextureElement>(normalPass->getTexture(), width / 4, height / 4));
        debugLayer.addElement(
                std::make_unique<TextureElement>(colorPass->getTexture(), width / 4, height / 4));

        uiSystem->addLayer(debugLayer);

        this->width = width;
        this->height = height;
        lights = createLights();
    }

    void DeferredRenderer::render(const std::vector<Entity> &entities, FpsCam &camera, const glm::mat4 &projection) {
//        simpleShader->use();
//        simpleShader->setViewMatrix(camera.getMatrix());
//        simpleShader->setProjectionMatrix(projection);

        for (const auto &item: entities) {
            positionPass->render(camera, item.model, projection, *item.mesh);
        }

        for (const auto &item: entities) {
            normalPass->render(camera, item.model, projection, *item.mesh);
        }

        //Set specular texture for now.
        colorShader->use();
        colorShader->setUniform("albedo", 0);
        colorShader->setUniform("specular", 1);
        specular.bind(1);

        for (const auto &item: entities) {
            colorPass->render(camera, item.model, projection, *item.mesh);
        }

        specular.unbind();

        //Now we draw the actual scene
        outputShader->use();
        outputShader->setUniform("positionTex", 0);
        outputShader->setUniform("normalTex", 1);
        outputShader->setUniform("albedoTex", 2);

        positionPass->getTexture().bind(0);
        normalPass->getTexture().bind(1);
        colorPass->getTexture().bind(2);

        outputShader->setProjectionMatrix(projection);
        outputShader->setModelMatrix(glm::mat4(1));
        outputShader->setViewMatrix(camera.getMatrix());
        outputShader->setUniform("cameraPos", camera.getPosition());

        setLights(*outputShader);

        glDisable(GL_DEPTH_TEST);
        glClearColor(1, 0.5, 0.5, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderQuad();

        positionBuffer->bind(GL_READ_FRAMEBUFFER);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        glBlitFramebuffer(0, 0, width, height, 0, 0, width, height,
                          GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        FBO::unbind();

//        lightShader->use();
//        lightShader->setUniform("projection", projection);
//        lightShader->setUniform("view", camera.getMatrix());
//
//        glm::mat4 model(1.0f);
//        for (int i = 0; i < lights.size(); i++) {
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, lights[i].Position);
//            model = glm::scale(model, glm::vec3(0.125f));
//            lightShader->setUniform("model", model);
//            lightShader->setUniform("lightColor", lights[i].Color);
//            renderCube();
//        }

        uiSystem->render();
    }


    void DeferredRenderer::renderQuad() {

        if (!quadVao) {
            std::vector<Vertex> vertices = {
                    Vertex::PT({-1.0f, 1.0f, -0.0f}, {0.0f, 1.0f}),
                    Vertex::PT({-1.0f, -1.0f, -0.0f}, {0.0f, 0.0f}),
                    Vertex::PT({1.0f, 1.0f, -0.0f}, {1.0f, 1.0f}),
                    Vertex::PT({1.0f, -1.0f, -0.0f}, {1.0f, 0.0f})
            };
            quadVao = VAO::create();
            quadVbo = VBO::create(vertices);

            quadVao->bind();
            quadVbo->bind();

            quadVao->addVertexBufferLayout(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
            quadVao->addVertexBufferLayout(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                           (void *) offsetof(Vertex, texcoord));

            quadVao->unbind();
            quadVbo->unbind();
        }
        quadVao->bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        quadVao->unbind();
    }

    std::vector<Light> DeferredRenderer::createLights() {
        std::vector<Light> lights;

        Light light;
        auto xPos = 0;
        auto yPos = 2;
        auto zPos = 0;
        light.Position = glm::vec3(xPos, yPos, zPos);

        auto rColor = 0.5f;
        auto gColor = 0.3f;
        auto bColor = 0.01f;
        light.Color = glm::vec3(rColor, gColor, bColor);
        lights.push_back(light);
//        for(int i = 0; i < NR_LIGHTS; i++) {
//            Light light;
//
//            auto xPos = static_cast<float>(((RandomUtils::RandomUtils::GetInstance()->generateInt(0, 100)) / 100.0) * 6.0 - 3.0);
//            auto yPos = static_cast<float>(((RandomUtils::RandomUtils::GetInstance()->generateInt(0, 100)) / 100.0) * 6.0 - 4.0);
//            auto zPos = static_cast<float>(((RandomUtils::RandomUtils::GetInstance()->generateInt(0, 100)) / 100.0) * 6.0 - 3.0);
//            light.Position = glm::vec3(xPos, yPos, zPos);
//
//            auto rColor = static_cast<float>(((rand() % 100) / 200.0f));// + 0.5); // between 0.5 and 1.)
//            auto gColor = static_cast<float>(((rand() % 100) / 200.0f));// + 0.5); // between 0.5 and 1.)
//            auto bColor = static_cast<float>(((rand() % 100) / 200.0f));// + 0.5); // between 0.5 and 1.)
//            light.Color = glm::vec3(rColor, gColor, bColor);
//
//
//            lights.push_back(light);
//        }

        return lights;
    }

    void DeferredRenderer::setLights(Shader &shader) {
        for (int i = 0; i < lights.size(); i++) {
            shader.setUniform("lights[" + std::to_string(i) + "].Position", lights[i].Position);
            shader.setUniform("lights[" + std::to_string(i) + "].Color", lights[i].Color);

            const float constant = 1.0f; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
            const float linear = 0.7f;
            const float quadratic = 1.8f;

            shader.setUniform("lights[" + std::to_string(i) + "].Linear", linear);
            shader.setUniform("lights[" + std::to_string(i) + "].Quadratic", quadratic);

            const float maxBrightness = std::fmaxf(std::fmaxf(lights[i].Color.r, lights[i].Color.g), lights[i].Color.b);
            float radius = (-linear +
                            std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) /
                           (2.0f * quadratic);
            shader.setUniform("lights[" + std::to_string(i) + "].Radius", radius);
        }
    }
} // nebula