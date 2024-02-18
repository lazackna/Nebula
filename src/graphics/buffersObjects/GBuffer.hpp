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
        Fbo fbo;
        Rbo rbo;
        std::vector<Texture> textures;
    public:
        enum class textureType {
            position,
            normal,
            albedoSpec,
            textureAmount
        };

        GBuffer(unsigned int width, unsigned int height);

        void addTextureAttachment(GLint internalFormat, GLenum format, GLenum type, GLenum attachment);
        void setDrawBuffers(const std::vector<GLenum>& attachments);
    };

} // nebula

#endif //NEBULA_MAIN_GBUFFER_HPP
