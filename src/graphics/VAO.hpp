//
// Created by User on 1/10/2024.
//

#ifndef NEBULA_MAIN_VAO_HPP
#define NEBULA_MAIN_VAO_HPP

#include <glad/glad.h>
#include <memory>
#include <vector>
#include "Vertex.hpp"

namespace nebula {
    class VAO;

    using Vao = std::unique_ptr<VAO>;

    class VAO {
        unsigned int id;
    public:
        VAO();

        ~VAO();

        void bind() const;

        static void unbind();

        void addVertexBufferLayout(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                                   const GLvoid *pointer) const;

        static Vao create();
    };

} // nebula

#endif //NEBULA_MAIN_VAO_HPP
