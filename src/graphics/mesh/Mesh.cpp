//
// Created by Jasper on 1/19/2024.
//

#include <iostream>
#include "Mesh.hpp"
#include "../../shaders/Shader.hpp"

namespace nebula {
    Mesh::Primitive::Primitive(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
                               const Material &material, const std::string &name) : name(name), size(vertices.size()), material(material) {
        setupMesh(vertices, indices);
    }

    void Mesh::Primitive::setupMesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) {
        vao = VAO::create();
        vbo = VBO::create(vertices);
        ebo = EBO::create(indices);
        vao->bind();
        vbo->bind();
        ebo->bind();

        vao->addVertexBufferLayout(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
        vao->addVertexBufferLayout(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
        vao->addVertexBufferLayout(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texcoord));
        vao->addVertexBufferLayout(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, color));

        vao->unbind();
        vbo->unbind();
        ebo->unbind();
    }

    void Mesh::Primitive::draw(Shader &shader) {

        material.use(shader);
        shader.use();

        vao->bind();
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(ebo->getSize()), GL_UNSIGNED_INT, nullptr);
        vao->unbind();
//        glBindVertexArray(0);
//        glUseProgram(0);
//        glActiveTexture(0);
//        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Mesh::draw(Shader &shader) {
        for (const auto &item: primitives) {
            item->draw(shader);
        }
    }

    void Mesh::addPrimitive(std::unique_ptr<Primitive> primitive) {
        primitives.push_back(std::move(primitive));
    }

} // nebula