//
// Created by Jasper on 2/7/2024.
//

#ifndef NEBULA_MAIN_GBUFFER_HPP
#define NEBULA_MAIN_GBUFFER_HPP

#include <glad/glad.h>
#include "FBO.hpp"
#include "RBO.hpp"
#include "../material/Texture.hpp"

namespace nebula {

    class GBuffer {
    public:
        struct fboTexture {
            GLenum attachment;
            Texture texture;
        };
    private:
        Fbo fbo;
        std::vector<Rbo> renderBuffers;
        std::vector<fboTexture> textureAttachments;

    public:
        GBuffer(int width, int height);

        void addTextureAttachment(GLint internalFormat, GLenum format, GLenum type, GLenum attachment, const std::string& name);
        void addRenderBuffer(GLenum format, GLenum attachment);
        [[nodiscard]] const std::vector<GBuffer::fboTexture> &getTextureAttachments() const;

        void bind() const;
        void unbind() const;
    };

} // nebula

#endif //NEBULA_MAIN_GBUFFER_HPP
