//
// Created by User on 2/7/2024.
//

#ifndef NEBULA_MAIN_RENDERINGPASS_HPP
#define NEBULA_MAIN_RENDERINGPASS_HPP

#include "buffersObjects/FBO.hpp"
#include "material/Texture.hpp"
#include "../shaders/Shader.hpp"
#include "mesh/Mesh.hpp"
#include "FpsCam.hpp"

namespace nebula {

    class RenderingPass {
        const Fbo& fbo;
        Texture texture;
        Shader& shader;

    public:
        RenderingPass(const Fbo& fbo, Shader& shader, const std::string& name);
        [[nodiscard]] Texture& getTexture();

        void render(FpsCam& camera, const glm::mat4& model, const glm::mat4& projection, Mesh& mesh);
    };

} // nebula

#endif //NEBULA_MAIN_RENDERINGPASS_HPP
