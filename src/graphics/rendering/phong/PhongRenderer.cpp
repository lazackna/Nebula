//
// Created by Jasper on 2/14/2024.
//

#include "PhongRenderer.hpp"
#include "../../../util/glUtil.hpp"

#include "../../../util/RandomUtils.hpp"

namespace nebula {
    void
    PhongRenderer::render(const std::vector<Entity> &entities, FpsCam &camera, const glm::mat4 &projection) {
        shader->use();
        shader->setViewMatrix(camera.getMatrix());
        shader->setProjectionMatrix(projection);

        glm::vec3 lightPos = glm::vec3(0,6,0);
        glm::vec3 lightColor = glm::vec3(1.0f / 255.0f,60.0f / 255.0f,60.0f / 255.0f);

        shader->setUniform("viewPos", camera.getPosition());

        shader->setUniform("lightColor", lightColor);
        shader->setUniform("lightPos", lightPos);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0., 0., 0., 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        setLights(*shader);

        for (const auto &item: entities) {
            item.draw(*shader);
        }

        //draw light
        glm::mat4 model(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
        lightShader->use();
        lightShader->setUniform("lightColor", lightColor);
        lightShader->setViewMatrix(camera.getMatrix());
        lightShader->setProjectionMatrix(projection);
        lightShader->setModelMatrix(model);

        drawCube();
    }

    PhongRenderer::PhongRenderer() {
        shader = std::make_shared<BasicShader>("resources/phong/shading");
        lightShader = std::make_shared<BasicShader>("resources/phong/light");

        lights = createLights();
    }

    std::vector<Light> PhongRenderer::createLights() {
        std::vector<Light> lights;

        for(int i = 0; i < 1; i++) {
            Light light;

            auto xPos = static_cast<float>(((RandomUtils::RandomUtils::GetInstance()->generateInt(0, 100)) / 100.0) * 6.0 - 3.0);
            auto yPos = static_cast<float>(((RandomUtils::RandomUtils::GetInstance()->generateInt(0, 100)) / 100.0) * 6.0 - 4.0);
            auto zPos = static_cast<float>(((RandomUtils::RandomUtils::GetInstance()->generateInt(0, 100)) / 100.0) * 6.0 - 3.0);
            light.Position = glm::vec3(xPos, yPos, zPos);

            auto rColor = static_cast<float>(((rand() % 100) / 200.0f));// + 0.5); // between 0.5 and 1.)
            auto gColor = static_cast<float>(((rand() % 100) / 200.0f));// + 0.5); // between 0.5 and 1.)
            auto bColor = static_cast<float>(((rand() % 100) / 200.0f));// + 0.5); // between 0.5 and 1.)
            light.Color = glm::vec3(rColor, gColor, bColor);


            lights.push_back(light);
        }

        return lights;
    }

    void PhongRenderer::setLights(Shader &shader) {
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