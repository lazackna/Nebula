//
// Created by Jasper on 12/24/2023.
//

#ifndef NEBULA_MAIN_NEBULA_HPP
#define NEBULA_MAIN_NEBULA_HPP

#include <string>
#include <memory>
#include <functional>

#include "NebulaOptions.hpp"
#include "../Window.hpp"


namespace nebula {

    class Nebula {
    private:
        NebulaOptions options;

        std::unique_ptr<Window> window;

        static Nebula* instance;
        std::optional<ErrorCallback> onError;
    private:
        void initialize();

        static void errorCallback(int error, const char* description);
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        static void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    public:
        explicit Nebula(NebulaOptions  options);

        void start();

        static Nebula& getInstance();
    };

} // nebula

#endif //NEBULA_MAIN_NEBULA_HPP
