//
// Created by Jasper on 12/24/2023.
//

#ifndef GLENGINE_WINDOW_HPP
#define GLENGINE_WINDOW_HPP

#include <GLFW/glfw3.h>
#include <memory>


#include "api/NebulaOptions.hpp"

namespace nebula {
    class Window {
    private:
        struct GLFWwindowDestroyer {
            void operator()(GLFWwindow* w) {
                if(w) {
                    glfwDestroyWindow(w);
                }
            }
        };

        std::unique_ptr<GLFWwindow, GLFWwindowDestroyer> window;

    public:
        explicit Window(const NebulaOptions& options);

        GLFWwindow* getWindow();
    };
}


#endif //GLENGINE_WINDOW_HPP
