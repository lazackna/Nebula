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
#include "../EBO.hpp"

#include "../material/Material.hpp"

namespace nebula {

    class Shader;

    class Mesh {
    public:
        class Primitive {
            std::string name;
            size_t size;
            Vao vao;
            Vbo vbo;
            Ebo ebo;

            Material material;
        public:
            Primitive(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Material& material, const std::string& name);
            void setupMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

            void draw(Shader &shader);
        };

        Mesh() = default;
        void addPrimitive(std::unique_ptr<Primitive> primitive);

        void draw(Shader &shader);
    private:
        std::vector<std::unique_ptr<Primitive>> primitives;
    };

} // nebula

#endif //NEBULA_MAIN_MESH_HPP
