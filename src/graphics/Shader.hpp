//
// Created by Jasper on 12/24/2023.
//

#ifndef NEBULA_MAIN_SHADER_HPP
#define NEBULA_MAIN_SHADER_HPP

#include <string>
#include <glad/glad.h>

namespace nebula {

    enum class ShaderType {
        Vertex,
        Fragment
    };

    class Shader {
        std::string shader;
        unsigned int id;
        const GLchar* source;
        bool valid = false;
        std::string errorMessage;

    public:
        explicit Shader(const std::string &shader, ShaderType type);
        ~Shader();
        [[nodiscard]] unsigned int getId() const;

        explicit operator bool() const {
            return valid;
        }

        void use();

    };

} // nebula

#endif //NEBULA_MAIN_SHADER_HPP
