//
// Created by Jasper on 1/19/2024.
//

#include "Mesh.hpp"


namespace nebula {
    Mesh::Primitive::Primitive(std::vector<Vertex>& vertices, const std::string &name) : name(name){
        size = vertices.size();
        setupMesh(vertices);
    }

    void Mesh::Primitive::setupMesh(std::vector<Vertex>& vertices) {
        vao = VAO::create();
        vbo = VBO::create(vertices);
        vao->bind();
        vbo->bind();

        vao->addVertexBufferLayout(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
        vao->addVertexBufferLayout(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));
        vao->addVertexBufferLayout(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texcoord));
        vao->addVertexBufferLayout(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, color));

        vao->unbind();
        vbo->unbind();
    }

    void Mesh::Primitive::draw() {
        vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, size);
        vao->unbind();
    }

    Mesh::Mesh(std::vector<Vertex> vertices, const std::string &name) {
        primitives.push_back(std::make_unique<Primitive>(vertices, name));
    }

    void Mesh::draw() {
        for (const auto &item: primitives) {
            item->draw();
        }
    }
} // nebula