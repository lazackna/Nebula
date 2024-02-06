//
// Created by User on 2/5/2024.
//

#include "Input.hpp"

namespace nebula {
    bool Input::getKey(unsigned int key) {
        return currentState.keys[key];
    }

    void Input::update() {
        currentState = previousState;
        previousState.keys.reset();
    }

    Input::Input(GLFWwindow* window) {

        auto lambda = [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            bool pressed = action == GLFW_PRESS;

            currentState.keys[key] = pressed;
        };
        glfwSetKeyCallback(window, lambda);
    }
} // nebula