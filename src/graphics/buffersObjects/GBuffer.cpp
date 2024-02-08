//
// Created by Jasper on 2/7/2024.
//

#include <iostream>
#include "GBuffer.hpp"

namespace nebula {
    GBuffer::GBuffer(int width, int height) {
        fbo = FBO::create(width, height);
    }

    void GBuffer::addTextureAttachment(GLint internalFormat, GLenum format, GLenum type, GLenum attachment, const std::string& name) {
        auto tex = std::make_shared<Texture>(fbo, internalFormat, format, type, attachment);
        tex->name = name;
        std::cout << "memory problem\n";
        textureAttachments.push_back({attachment, std::move(tex)});
        std::cout << "passed push\n";
    }

    const std::vector<GBuffer::fboTexture> &GBuffer::getTextureAttachments() const {
        return textureAttachments;
    }

    void GBuffer::addRenderBuffer(GLenum format, GLenum attachment) {
        renderBuffers.push_back(RBO::create(fbo, format, attachment));
    }

    void GBuffer::bind(GLenum target) const {
        fbo->bind(target);
    }

    void GBuffer::unbind(GLenum target) const {
        fbo->unbind(target);
    }
} // nebula