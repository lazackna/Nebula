//
// Created by Jasper on 1/18/2024.
//

#include <vector>
#include <iostream>
#include "Texture.hpp"
#include "../../stb/image.hpp"


namespace nebula {
    Texture::Texture(const std::filesystem::path &filePath, Texture::Wrap wrapS, Texture::Wrap wrapT) {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(filePath.string().c_str(), &width, &height, &nrChannels, 0);
        stbi__vertical_flip(data, width, height, nrChannels);
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

    void Texture::bind(int unit) const {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, textureId);
    }

    void Texture::unbind() {
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::Texture(const glm::vec4 &color) {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        stbi_uc imgData[4] = {(stbi_uc) (color.r * 255), (stbi_uc) (color.g * 255), (stbi_uc) (color.b * 255),
                              (stbi_uc) (color.a * 255)};
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

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::Texture(const std::vector<glm::vec4> &colors, int width, int height) {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        std::vector<stbi_uc> imgData;

        for (auto &c: colors) {
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

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::Texture(std::vector<unsigned char> &data, int width, int height, GLenum format, GLenum type) {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                     format, type, &data.at(0));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::Texture(const Fbo &fbo, GLint internalFormat, GLenum format, GLenum type, GLenum attachment) {
        fbo->bind();

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        std::cout << "generated texture\n";
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, fbo->getWidth(), fbo->getHeight(), 0, format, type, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        std::cout << "making framebuffer texture\n";
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, textureId, 0);
        std::cout << "making framebuffer texture succesful\n";
        glBindTexture(GL_TEXTURE_2D, 0);

        fbo->unbind();
    }

    unsigned int Texture::getTextureId() const {
        return textureId;
    }

    Texture::~Texture() {
        glDeleteTextures(GL_TEXTURE_2D, &textureId);
    }
} // nebula