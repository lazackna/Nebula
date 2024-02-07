//
// Created by Jasper on 2/4/2024.
//

#include "FBO.hpp"

#include <glad/glad.h>

namespace nebula {
    FBO::FBO(int width, int height) : width(width), height(height){
        glGenFramebuffers(1, &id);
    }

    FBO::~FBO() {
        glDeleteFramebuffers(1, &id);
    }

    void FBO::bind() const{
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

    void FBO::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Fbo FBO::create(int width, int height) {
        return std::make_unique<FBO>(width, height);
    }

    int FBO::getWidth() const {
        return width;
    }

    int FBO::getHeight() const {
        return height;
    }
} // nebula