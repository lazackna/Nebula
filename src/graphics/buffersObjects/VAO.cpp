//
// Created by User on 1/10/2024.
//

#include "VAO.hpp"

#include <glad/glad.h>

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

    void VAO::addVertexBufferLayout(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride,
                                    const void *pointer) const {
        bind();
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        unbind();
    }

    Vao VAO::create() {
        return std::make_unique<VAO>();
    }
} // nebula