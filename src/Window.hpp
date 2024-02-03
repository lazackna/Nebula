//
// Created by Jasper on 12/24/2023.
//

#ifndef GLENGINE_WINDOW_HPP
#define GLENGINE_WINDOW_HPP

#include <memory>


#include "api/NebulaOptions.hpp"

struct GLFWwindow;

namespace nebula {
    class Window {
    private:
        struct GLFWwindowDestroyer {
            void operator()(GLFWwindow* w);
        };

        std::unique_ptr<GLFWwindow, GLFWwindowDestroyer> window;

    public:
        explicit Window(const NebulaOptions& options);

        GLFWwindow* getWindow();
    };
}


#endif //GLENGINE_WINDOW_HPP
