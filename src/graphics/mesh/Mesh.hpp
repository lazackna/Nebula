//
// Created by Jasper on 1/19/2024.
//

#ifndef NEBULA_MAIN_MESH_HPP
#define NEBULA_MAIN_MESH_HPP

#include <vector>
#include <string>
#include "../Vertex.hpp"

namespace nebula {

    class Mesh {
        class Primitive {
            std::string name;
            std::vector<Vertex> vertices;
            unsigned int VAO;

            Primitive(std::vector<Vertex> vertices, const std::string& name);
            void setupMesh();
        };

        unsigned int vbo;
    };

} // nebula

#endif //NEBULA_MAIN_MESH_HPP
