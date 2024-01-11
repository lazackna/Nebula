//
// Created by User on 1/10/2024.
//

#include "Graphics.hpp"
#include "VBO.hpp"


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
        static Vertex tmpVertex;
        if (vbo->size > 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo->id);

            glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex),	(void*) ((char*)&tmpVertex.position - (char*)&tmpVertex));
            glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex),		(void*) ((char*)&tmpVertex.color - (char*)&tmpVertex));
            glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex),	(void*) ((char*)&tmpVertex.texcoord - (char*)&tmpVertex));
            glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex),	(void*) ((char*)&tmpVertex.normal - (char*)&tmpVertex));
            glDrawArrays(shape, 0, (GLsizei)vbo->size);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }

    VBO::~VBO() {
        glDeleteBuffers(1, &id);
    }
}
