//
// Created by Jasper on 2/14/2024.
//

#ifndef NEBULA_MAIN_PHONGRENDERER_HPP
#define NEBULA_MAIN_PHONGRENDERER_HPP
#include "../Renderer.hpp"
#include "../../../shaders/BasicShader.hpp"
#include "../../../shaders/light/lighting.hpp"
namespace nebula {

    class PhongRenderer : public Renderer{
        std::shared_ptr<BasicShader> shader;
        std::shared_ptr<BasicShader> lightShader;

        std::vector<Light> lights;

        void setLights(Shader &shader);

        std::vector<Light> createLights();
    public:
        PhongRenderer();
        void render(const std::vector<Entity> &entities, FpsCam &camera, const glm::mat4 &projection) override;
    };

} // nebula

#endif //NEBULA_MAIN_PHONGRENDERER_HPP
