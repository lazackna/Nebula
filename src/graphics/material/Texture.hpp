//
// Created by Jasper on 1/18/2024.
//

#ifndef NEBULA_MAIN_TEXTURE_HPP
#define NEBULA_MAIN_TEXTURE_HPP

#include <glad/glad.h>
#include <glm/vec4.hpp>
#include "filesystem"
#include <vector>

namespace nebula {

    class Texture {
        GLuint textureId = -1;
    public:
        enum class Filter
        {
            Nearest = GL_NEAREST,
            Linear = GL_LINEAR
        };

        enum class Wrap
        {
            ClampToBorder = GL_CLAMP_TO_BORDER,
            ClampToEdge = GL_CLAMP_TO_EDGE,
            ClampToEdgeMirrored = GL_MIRROR_CLAMP_TO_EDGE,
            Repeat = GL_REPEAT,
            RepeatMirrored = GL_MIRRORED_REPEAT
        };

        explicit Texture(const std::filesystem::path& filePath, Wrap wrapS = Wrap::Repeat, Wrap wrapT = Wrap::Repeat);

        void bind() const;
        static void unbind();

        explicit Texture(const glm::vec4& color);
        explicit Texture(const std::vector<glm::vec4>& colors, int width, int height);
    };

} // nebula

#endif //NEBULA_MAIN_TEXTURE_HPP
