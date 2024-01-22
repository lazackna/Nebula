//
// Created by Jasper on 1/22/2024.
//

#include <glad/glad.h>
#include "EBO.hpp"

namespace nebula {
    EBO::EBO(const std::vector<unsigned int> &indices) {

        size = indices.size();

        glGenBuffers(1, &id);
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        unbind();
    }

    void EBO::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void EBO::unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    Ebo EBO::create(const std::vector<unsigned int> &indices) {
        return std::make_unique<EBO>(indices);
    }

    size_t EBO::getSize() const {
        return size;
    }
} // nebula