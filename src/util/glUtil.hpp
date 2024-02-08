//
// Created by Jasper on 1/19/2024.
//

#ifndef NEBULA_MAIN_GLUTIL_HPP
#define NEBULA_MAIN_GLUTIL_HPP

#include <glm/ext/matrix_clip_space.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>

glm::mat4 createPerspective(float fov, float aspectRatio, float nearPlane, float farPlane) {
    return glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

glm::mat4 createOrthographic(float left, float right, float bottom, float top) {
    return glm::ortho(left, right, bottom, top);
}

void enableWireframe(bool enable) {
    if(enable) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void checkGLError(const char* file, int line) {
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
            case GL_INVALID_ENUM:
                error = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error = "GL_INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                error = "GL_STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                error = "GL_STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                error = "GL_OUT_OF_MEMORY";
                break;
            default:
                error = "Unknown error";
                break;
        }
        std::cout << "OpenGL error in file " << file << " at line " << line << ": " << error << std::endl;
    }
}

#endif //NEBULA_MAIN_GLUTIL_HPP
