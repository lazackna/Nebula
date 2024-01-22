//
// Created by Jasper on 1/11/2024.
//

#include "BasicShader.hpp"

namespace nebula {
    void BasicShader::setModelMatrix(const glm::mat4 &modelMatrix) {
        this->modelMatrix = modelMatrix;
        setUniform("modelMatrix", modelMatrix);
        setUniform("normalMatrix", glm::mat3(glm::transpose(glm::inverse(modelMatrix))));
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

    }
} // nebula