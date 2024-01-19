//
// Created by Jasper on 1/18/2024.
//

#include <vector>
#include "Texture.hpp"
#include "../stb/image.hpp"

namespace nebula {
    Texture::Texture(const std::filesystem::path &filePath, Texture::Wrap wrapS, Texture::Wrap wrapT) {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(filePath.string().c_str(), &width, &height, &nrChannels, 0);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    void Texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
} // nebula