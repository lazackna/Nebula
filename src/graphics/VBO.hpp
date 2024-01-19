//
// Created by Jasper on 1/19/2024.
//

#ifndef NEBULA_MAIN_VBO_HPP
#define NEBULA_MAIN_VBO_HPP

#include <memory>
#include <vector>
#include "Vertex.hpp"

namespace nebula {
    class VBO;
    using Vbo = std::unique_ptr<VBO>;

    class VBO {
        unsigned int id;
    public:
        explicit VBO(const std::vector<Vertex>& vertices);
        ~VBO();
        void bind() const;
        static void unbind();

        static Vbo create(const std::vector<Vertex>& vertices);
    };

} // nebula

#endif //NEBULA_MAIN_VBO_HPP
