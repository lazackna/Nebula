//
// Created by Jasper on 2/7/2024.
//

#include "RBO.hpp"

namespace nebula {
    RBO::RBO(const Fbo& fbo, GLenum format, GLenum attachment) : id(-1) {
        fbo->bind();
        glGenRenderbuffers(1, &id);
        glBindRenderbuffer(GL_RENDERBUFFER, id);
        glRenderbufferStorage(GL_RENDERBUFFER, format, fbo->getWidth(), fbo->getHeight()); // use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, id); // now actually attach it
        fbo->unbind();
    }

    Rbo RBO::create(const Fbo &fbo, GLenum format, GLenum attachment) {
        return std::make_unique<RBO>(fbo, format, attachment);
    }

    RBO::~RBO() {
        glDeleteRenderbuffers(1, &id);
    }
} // nebula