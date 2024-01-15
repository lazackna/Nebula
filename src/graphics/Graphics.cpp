//
// Created by User on 1/10/2024.
//

#include "Graphics.hpp"
#include "VAO.hpp"


#include <memory>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace nebula {
    Vao createVao(const std::vector<Vertex> &vertices) {
        Vao vao = std::make_unique<VAO>();
        glGenVertexArrays(1, &vao->id);
        vao->bind();

        GLuint vertexBuffer;
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 48, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 48, BUFFER_OFFSET(12));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 48, BUFFER_OFFSET(24));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 48, BUFFER_OFFSET(32));

        vao->unbind();
        return vao;
    }

    void drawVertices(GLenum shape, Vao &vbo) {
        if (vbo->size > 0)
        {
            glBindVertexArray(vbo->id);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

            glDrawArrays(shape, 0, (GLsizei)vbo->size);

            glBindVertexArray(0);
        }
    }

    VAO::~VAO() {
        glDeleteBuffers(1, &id);
    }
}
