//
// Created by Jasper on 12/24/2023.
//

#include "Shader.hpp"

#include <glad/glad.h>

namespace nebula {
    Shader::Shader(const std::string &shader, ShaderType type) : shader(shader) {
        switch (type) {
            case ShaderType::Vertex:
                id = glCreateShader(GL_VERTEX_SHADER);
                break;
            case ShaderType::Fragment:
                id = glCreateShader(GL_FRAGMENT_SHADER);
                break;
        }
        source = shader.c_str();
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        int success;
        char infoLog[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        valid = success;

        if(!success) {
            glGetShaderInfoLog(id, 512, nullptr, infoLog);
            errorMessage = infoLog;
            return;
        }
    }

    unsigned int Shader::getId() const {
        return id;
    }

    Shader::~Shader() {
        glDeleteShader(id);
    }
} // nebula