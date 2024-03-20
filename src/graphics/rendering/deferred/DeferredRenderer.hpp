//
// Created by Jasper on 2/13/2024.
//

#ifndef NEBULA_MAIN_DEFERREDRENDERER_HPP
#define NEBULA_MAIN_DEFERREDRENDERER_HPP

#include "../Renderer.hpp"
#include "../../../shaders/BasicShader.hpp"
#include "../../buffersObjects/GBuffer.hpp"
#include "../../RenderingPass.hpp"
#include "../../../shaders/light/lighting.hpp"
#include "../../../ui/UISystem.hpp"

#ifndef NR_LIGHTS
#define NR_LIGHTS 16
#endif

namespace nebula {

    class DeferredRenderer : public Renderer{
        std::unique_ptr<GBuffer> gBuffer;

        Fbo positionBuffer;
        Rbo positionRbo;
        std::unique_ptr<BasicShader> positionShader;
        std::unique_ptr<RenderingPass> positionPass;

        Fbo normalBuffer;
        Rbo normalRbo;
        std::unique_ptr<BasicShader> normalShader;
        std::unique_ptr<RenderingPass> normalPass;

        Fbo colorBuffer;
        Rbo colorRbo;
        std::unique_ptr<BasicShader> colorShader;
        std::unique_ptr<RenderingPass> colorPass;

        std::unique_ptr<BasicShader> outputShader;
        std::unique_ptr<BasicShader> lightShader;

        Texture specular = Texture(glm::vec4(0.1f, 0, 0, 0));

        std::unique_ptr<UISystem> uiSystem;

        Vao quadVao;
        Vbo quadVbo;

        Vao cubeVao;
        Vbo cubeVbo;

        int width, height;

        const int maxLights = 32;
        std::vector<Light> lights;

    public:
        DeferredRenderer(unsigned int width, unsigned int height, const std::unique_ptr<Window>& window);

        void render(const std::vector<Entity> &entities, FpsCam &camera, const glm::mat4 &projection) override;

        void renderQuad();

        static std::vector<Light> createLights();
        void setLights(Shader& shader);

    };

} // nebula

#endif //NEBULA_MAIN_DEFERREDRENDERER_HPP
