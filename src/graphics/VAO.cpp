//
// Created by User on 1/10/2024.
//

#include "VAO.hpp"

namespace nebula {

    void VAO::bind() const {
        glBindVertexArray(id);
    }

    void VAO::unbind() {
        glBindVertexArray(0);
    }

    VAO::VAO() : id(-1) {
        glGenVertexArrays(1, &id);
    }

    VAO::~VAO() {
        glDeleteVertexArrays(1, &id);
    }

    void VAO::addVertexBufferLayout(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                                    const GLvoid *pointer) const {
        bind();
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        unbind();
    }
} // nebula