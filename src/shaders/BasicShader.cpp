//
// Created by Jasper on 1/11/2024.
//

#include "BasicShader.hpp"

#include "../graphics/material/Material.hpp"

namespace nebula {
    void BasicShader::setModelMatrix(const glm::mat4 &modelMatrix) {
        this->modelMatrix = modelMatrix;
        setUniform("modelMatrix", modelMatrix);
        this->normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
        setUniform("normalMatrix", this->normalMatrix);
    }

    void BasicShader::setProjectionMatrix(const glm::mat4 &projectionMatrix) {
        this->projectionMatrix = projectionMatrix;
        setUniform("projectionMatrix", projectionMatrix);
    }

    void BasicShader::setViewMatrix(const glm::mat4 &viewMatrix) {
        this->viewMatrix = viewMatrix;
        setUniform("viewMatrix", viewMatrix);
    }

    BasicShader::BasicShader(const std::string &shader) : Shader(shader), projectionMatrix(1.0f), modelMatrix(1.0f), viewMatrix(1.0f) {}

    void BasicShader::setMaterial(const Material &material) {
        for(int index = static_cast<int>(TextureType::ALBEDO); static_cast<TextureType>(index) != TextureType::ROUGHNESS; index++) {
            TextureType tt = static_cast<TextureType>(index);

            auto it = material.getTextureMap().find(tt);
            if (it != material.getTextureMap().end()) {
                if (tt == TextureType::ALBEDO) {
                    //setUniform("ourTexture", 0);
                    //setDiffuseTexture(0);
                    it->second->bind(0);
                }
                if (tt == TextureType::METALLICROUGHNESS) {
                    //setNormalTexture(1);
                    //it->second->bind(1);
                }
            }
        }
    }
} // nebula