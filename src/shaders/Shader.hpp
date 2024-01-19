//
// Created by Jasper on 12/24/2023.
//

#ifndef NEBULA_MAIN_SHADER_HPP
#define NEBULA_MAIN_SHADER_HPP

#include <string>
#include <map>
#include <glad/glad.h>
#include "filesystem"

#include "glm/gtc/type_ptr.hpp"

namespace nebula {

    class Shader {
        std::string shader;
        GLuint programId = -1;
        bool valid = false;
        std::string errorMessage;

        std::map<std::string, GLint> uniforms;

    public:
        explicit Shader(const std::string &shader);
        ~Shader();
        [[nodiscard]] unsigned int getProgramId() const;

        explicit inline operator bool() const {
            return programId != -1;
        }

        void use() const;

        //virtual void setMaterial(const Material &material) = 0;

        // Sets the projection matrix
        virtual void setProjectionMatrix(const glm::mat4 &matrix) = 0;

        // Sets the view (camera) matrix
        virtual void setViewMatrix(const glm::mat4 &matrix) = 0;

        // Sets the model matrix
        virtual void setModelMatrix(const glm::mat4 &matrix) = 0;

        GLint getUniform(const std::string& name);

        void setUniform(const std::string& uniform, const glm::mat4& value);
        void setUniform(const std::string& uniform, const glm::mat3& value);
        void setUniform(const std::string& uniform, const glm::mat2& value);
        void setUniform(const std::string& uniform, const glm::vec4& value);
        void setUniform(const std::string& uniform, const glm::vec3& value);
        void setUniform(const std::string& uniform, const glm::vec2& value);
        void setUniform(const std::string& uniform, float value);
        void setUniform(const std::string& uniform, int value);
        void setUniform(const std::string& uniform, bool value);

    protected:
        static bool createShader(const std::filesystem::path &shaderPath, GLenum shaderType, GLuint& shaderId);
        static std::string readShaderData(const std::filesystem::path& shaderPath);
    };

} // nebula

#endif //NEBULA_MAIN_SHADER_HPP
