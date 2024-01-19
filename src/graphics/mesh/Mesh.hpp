//
// Created by Jasper on 1/19/2024.
//

#ifndef NEBULA_MAIN_MESH_HPP
#define NEBULA_MAIN_MESH_HPP

#include <vector>
#include <string>
#include "../Vertex.hpp"

#include "../VAO.hpp"
#include "../VBO.hpp"

namespace nebula {

    class Mesh {
    public:
        class Primitive {
            std::string name;
            size_t size;
            Vao vao;
            Vbo vbo;
        public:
            Primitive(std::vector<Vertex>& vertices, const std::string& name);
            void setupMesh(std::vector<Vertex>& vertices);

            void draw();
        };

        Mesh(std::vector<Vertex> vertices, const std::string& name);
        void draw();

    private:
        std::vector<std::unique_ptr<Primitive>> primitives;
    };

} // nebula

#endif //NEBULA_MAIN_MESH_HPP
