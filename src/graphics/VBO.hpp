//
// Created by User on 1/10/2024.
//

#ifndef NEBULA_MAIN_VBO_HPP
#define NEBULA_MAIN_VBO_HPP
#include <glad/glad.h>
#include <memory>
#include <vector>
#include "Vertex.hpp"

namespace nebula {
    class VBO;
    using Vbo = std::unique_ptr<VBO>;
    class VBO {
        GLuint id;
        size_t size;
        friend void drawVertices(GLenum shape, Vbo& vbo);
        friend Vbo createVbo(const std::vector<Vertex>& vertices);

    public:
        ~VBO();
    };

} // nebula

#endif //NEBULA_MAIN_VBO_HPP
