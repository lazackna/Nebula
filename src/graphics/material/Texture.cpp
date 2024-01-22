//
// Created by Jasper on 1/18/2024.
//

#include <vector>
#include "Texture.hpp"
#include "../../stb/image.hpp"

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

    void Texture::unbind() {
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::Texture(const glm::vec4 &color) {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        stbi_uc imgData[4] = {(stbi_uc)(color.r * 255), (stbi_uc)(color.g * 255), (stbi_uc)(color.b * 255), (stbi_uc)(color.a * 255)};
        glTexImage2D(GL_TEXTURE_2D,
                     0, //level
                     GL_RGBA, //internal format
                     1, //width
                     1, //height
                     0, //border
                     GL_RGBA, //data format
                     GL_UNSIGNED_BYTE, //data type
                     imgData);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::Texture(const std::vector<glm::vec4> &colors, int width, int height) {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        std::vector<stbi_uc> imgData;

        for(auto& c : colors) {
            imgData.push_back(static_cast<stbi_uc>(c.r * 255));
            imgData.push_back(static_cast<stbi_uc>(c.g * 255));
            imgData.push_back(static_cast<stbi_uc>(c.b * 255));
            imgData.push_back(static_cast<stbi_uc>(c.a * 255));
        }

        //stbi_uc imgData[4] = {(stbi_uc)(color.r * 255), (stbi_uc)(color.g * 255), (stbi_uc)(color.b * 255), (stbi_uc)(color.a * 255)};
        glTexImage2D(GL_TEXTURE_2D,
                     0, //level
                     GL_RGBA, //internal format
                     width, //width
                     height, //height
                     0, //border
                     GL_RGBA, //data format
                     GL_UNSIGNED_BYTE, //data type
                     &imgData[0]);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        //glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
} // nebula