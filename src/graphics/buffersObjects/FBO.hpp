//
// Created by Jasper on 2/4/2024.
//

#ifndef NEBULA_MAIN_FBO_HPP
#define NEBULA_MAIN_FBO_HPP

#include <memory>

namespace nebula {

    class FBO;
    using Fbo = std::unique_ptr<FBO>;

    class FBO {
        unsigned int id;

        int width = 0;
        int height = 0;
    public:
        FBO(int width, int height);

        ~FBO();
        void bind();
        static void unbind();

        static Fbo create(int width, int height);

        [[nodiscard]] int getWidth() const;

        [[nodiscard]] int getHeight() const;
    };

} // nebula

#endif //NEBULA_MAIN_FBO_HPP