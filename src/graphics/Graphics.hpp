//
// Created by User on 1/10/2024.
//

#ifndef NEBULA_MAIN_GRAPHICS_HPP
#define NEBULA_MAIN_GRAPHICS_HPP

#include <memory>
#include <vector>

#include "VBO.hpp"

namespace nebula {
    Vbo createVbo(const std::vector<Vertex> &vertices); // NOLINT(*-redundant-declaration)
    void drawVertices(GLenum shape, Vbo& vbo); // NOLINT(*-redundant-declaration)
} // nebula
// Graphics

#endif //NEBULA_MAIN_GRAPHICS_HPP
