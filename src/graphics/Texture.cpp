//
// Created by Jasper on 1/18/2024.
//

#include <vector>
#include "Texture.hpp"
#include "lodepng.h"

namespace nebula {
    Texture::Texture(const std::filesystem::path &filePath, Texture::Wrap wrapS, Texture::Wrap wrapT) {
        std::vector<unsigned char> image;
        unsigned int width, height;
        auto error = lodepng::decode(image, width, height, filePath.string());

        if(error != 0) {
            printf("[lodepng] Error = {}, Message = {}", error, lodepng_error_text(error));
            return;
        }

        glGenTextures(1, &textureId);

        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &image[0]);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void Texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
} // nebula