//
// Created by Jasper on 1/19/2024.
//

#include "VBO.hpp"

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace nebula {
    VBO::VBO(const std::vector<Vertex> &vertices) : id(-1){
        glGenBuffers(1, &id);
        bind();
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        unbind();
    }

    void VBO::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VBO::unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VBO::~VBO() {
        glDeleteBuffers(1, &id);
    }
} // nebula