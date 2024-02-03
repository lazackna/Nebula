//
// Created by Jasper on 12/24/2023.
//

#include "Window.hpp"

#include <GLFW/glfw3.h>

namespace nebula {
    Window::Window(const NebulaOptions& options) {
        window = std::unique_ptr<GLFWwindow, GLFWwindowDestroyer>(
                glfwCreateWindow(options.width, options.height, options.name.c_str(), nullptr, nullptr));
    }

    GLFWwindow *Window::getWindow() {
        return &*window;
    }

    void Window::GLFWwindowDestroyer::operator()(GLFWwindow *w) {
        if(w) {
            glfwDestroyWindow(w);
        }
    }
}
