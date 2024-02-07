//
// Created by Jasper on 2/7/2024.
//

#ifndef NEBULA_MAIN_RBO_HPP
#define NEBULA_MAIN_RBO_HPP

#include <memory>

#include "glad/glad.h"
#include "FBO.hpp"

namespace nebula {

    class RBO;
    using Rbo = std::unique_ptr<RBO>;

    class RBO {
        unsigned int id;

    public:
        explicit RBO(const Fbo& fbo, GLenum format, GLenum attachment);
        ~RBO();

        static Rbo create(const Fbo& fbo, GLenum format, GLenum attachment);
    };

} // nebula

#endif //NEBULA_MAIN_RBO_HPP
