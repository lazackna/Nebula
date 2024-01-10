//
// Created by User on 1/10/2024.
//

#include "Graphics.hpp"

#include <memory>

namespace nebula {
    Vbo createVbo(const std::vector<Vertex> &vertices) {
        Vbo vbo = std::make_unique<VBO>();
        glGenBuffers(1, &vbo->id);
        glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        vbo->size = vertices.size();
        return vbo;
    }

    void drawVertices(GLenum shape, Vbo &vbo) {
        
    }
}
