//
// Created by User on 1/10/2024.
//
#ifndef NEBULA_MAIN_VERTEX_HPP
#define NEBULA_MAIN_VERTEX_HPP

#include <glm/glm.hpp>

namespace nebula {
    struct Vertex
    {
    public:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec4 color;
        glm::vec2 texcoord;

        // Creates a vertex with a position
        static Vertex P(const glm::vec3& position) {
            return { position, glm::vec3(0,1,0), glm::vec4(1,1,1,1), glm::vec2(0,0) };
        }

        // Creates a vertex with a position and a color
        static Vertex PC(const glm::vec3& position, const glm::vec4& color) {
            return { position, glm::vec3(0,1,0), color, glm::vec2(0,0) };
        }

        // Creates a vertex with a position and a texture coordinat
        static Vertex PT(const glm::vec3& position, const glm::vec2& texcoord) {
            return { position, glm::vec3(0,1,0), glm::vec4(1,1,1,1), texcoord };
        }

        // Creates a vertex with a position and a normal
        static Vertex PN(const glm::vec3& position, const glm::vec3& normal) {
            return { position, normal, glm::vec4(1,1,1,1), glm::vec2(0,0) };
        }

        // Creates a vertex with a position, a texture coordinat and a color
        static Vertex PTC(const glm::vec3& position, const glm::vec2& texcoord, const glm::vec4& color) {
            return { position, glm::vec3(0,1,0), color, texcoord };
        }


        // Creates a vertex with a position, color and normal
        static Vertex PCN(const glm::vec3& position, const glm::vec4& color, const glm::vec3& normal) {
            return { position, normal, color, glm::vec2(0,0) };
        }

        // Creates a vertex with a position, texture coordinat and normal
        static Vertex PTN(const glm::vec3& position, const glm::vec2& texcoord, const glm::vec3& normal) {
            return { position, normal, glm::vec4(1,1,1,1), texcoord };
        }

        // Creates a vertex with a position, color, texture coordinat and normal
        static Vertex PCTN(const glm::vec3& position, const glm::vec4& color, const glm::vec2& texcoord, const glm::vec3& normal) {
            return { position, normal, color, texcoord };
        }

        bool operator == (const Vertex& other) {
            return position == other.position && normal == other.normal
            && color == other.color && texcoord == other.texcoord;
        }
    };
}

#endif //NEBULA_MAIN_VERTEX_HPP
