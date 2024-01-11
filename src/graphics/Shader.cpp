//
// Created by Jasper on 12/24/2023.
//

#include "Shader.hpp"

#include <iostream>
#include "fstream"

#include <glad/glad.h>
#include <cstring>

namespace nebula {

    bool checkShaderErrors(GLuint shaderId, const std::filesystem::path& shaderPath)
    {
        GLint status;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);					//kijk of het compileren is gelukt
        if (status == GL_FALSE)
        {
            int length, charsWritten;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);				//haal de lengte van de foutmelding op
            char* infolog = new char[length + 1];
            memset(infolog, 0, length + 1);
            glGetShaderInfoLog(shaderId, length, &charsWritten, infolog);		//en haal de foutmelding zelf op
            std::cout << "Error compiling shader " << shaderPath.string() << ":\n" << infolog << std::endl;
            delete[] infolog;
            return true;
        }
        return false;
    }

    Shader::Shader(const std::string &shader) : shader(shader) {
        if(programId != -1) {
            glDeleteProgram(programId);
        }

        programId = glCreateProgram();

        GLuint vertexId;
        if(!createShader(shader + ".vert", GL_VERTEX_SHADER, vertexId)) {
            glDeleteProgram(programId);
            programId = -1;
            return;
        }
        glAttachShader(programId, vertexId);

        glBindAttribLocation(programId, 0, "a_position");
        glEnableVertexAttribArray(0);
        glBindAttribLocation(programId, 1, "a_color");
        glEnableVertexAttribArray(1);
        glBindAttribLocation(programId, 2, "a_texcoord");
        glEnableVertexAttribArray(2);
        glBindAttribLocation(programId, 3, "a_normal");
        glEnableVertexAttribArray(3);

        GLuint fragmentId;
        if(!createShader(shader + ".frag", GL_FRAGMENT_SHADER, fragmentId)) {
            glDeleteProgram(programId);
            programId = -1;
            return;
        }
        glAttachShader(programId, fragmentId);

        glLinkProgram(programId);
        glUseProgram(programId);
    }

    unsigned int Shader::getProgramId() const {
        return programId;
    }

    Shader::~Shader() {
        glDeleteShader(programId);
    }

    void Shader::use() const {
        glUseProgram(programId);
    }

    std::string Shader::readShaderData(const std::filesystem::path &shaderPath) {
        std::ifstream shaderFile(shaderPath.string());
        std::string vertexShaderData((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());

        return vertexShaderData;
    }

    bool Shader::createShader(const std::filesystem::path &shaderPath, GLenum shaderType, GLuint &shaderId) {
        shaderId = glCreateShader(shaderType);
        std::string data =  readShaderData(shaderPath);
        const char* pData = data.c_str();
        glShaderSource(shaderId, 1, &pData, nullptr);
        glCompileShader(shaderId);

        return !checkShaderErrors(shaderId, shaderPath);
    }

    GLint Shader::getUniform(const std::string &name) {
        auto it = uniforms.find(name);
        if(it != uniforms.end()) {
            return it->second;
        }
        GLint location = glGetUniformLocation(programId, name.c_str());
        uniforms[name] = location;
        return location;
    }

    void Shader::setUniform(const std::string &name, const glm::mat4 &mat) {
        glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void Shader::setUniform(const std::string &uniform, const glm::mat3 &value) {
        glUniformMatrix3fv(getUniform(uniform), 1, false, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string &uniform, const glm::vec4 &value) {
        glUniform4fv(getUniform(uniform), 1, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string &uniform, const glm::vec3 &value) {
        glUniform3fv(getUniform(uniform), 1, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string &uniform, const glm::vec2 &value) {
        glUniform2fv(getUniform(uniform), 1, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string &uniform, float value) {
        glUniform1f(getUniform(uniform), value);
    }

    void Shader::setUniform(const std::string &uniform, int value) {
        glUniform1i(getUniform(uniform), value);
    }

    void Shader::setUniform(const std::string &uniform, bool value) {
        glUniform1i(getUniform(uniform), value);
    }
} // nebula