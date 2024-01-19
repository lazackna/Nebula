//
// Created by Jasper on 1/11/2024.
//

#ifndef NEBULA_MAIN_BASICSHADER_HPP
#define NEBULA_MAIN_BASICSHADER_HPP

#include "Shader.hpp"

namespace nebula {

    class BasicShader : public Shader{
        glm::mat4 modelMatrix;
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat3 normalMatrix;

    public:
        explicit BasicShader(const std::string &shader);

        void setModelMatrix(const glm::mat4 &modelMatrix);

        void setProjectionMatrix(const glm::mat4 &projectionMatrix);

        void setViewMatrix(const glm::mat4 &viewMatrix);

        void setNormalMatrix(const glm::mat3 &normalMatrix);
    };

} // nebula

#endif //NEBULA_MAIN_BASICSHADER_HPP
