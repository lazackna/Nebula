//
// Created by User on 2/5/2024.
//

#ifndef NEBULA_MAIN_INPUT_HPP
#define NEBULA_MAIN_INPUT_HPP

//Just making sure glad is included earlier
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bitset>

namespace nebula {

    class Input {
        struct keyboardState {
            std::bitset<GLFW_KEY_LAST> keys;
        };

        keyboardState currentState;
        keyboardState previousState;

    public:
        Input(GLFWwindow* window);

        void update();

        bool getKey(unsigned int key);
    };

} // nebula

#endif //NEBULA_MAIN_INPUT_HPP
