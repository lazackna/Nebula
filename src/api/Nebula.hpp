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

#include "input/Input.hpp"
#include "../graphics/buffersObjects/VAO.hpp"
#include "../graphics/buffersObjects/VBO.hpp"
#include "../shaders/light/lighting.hpp"

#define NR_LIGHTS 32

namespace nebula {

    class Shader;

    class Nebula {
    private:
        NebulaOptions options;

        std::unique_ptr<Window> window;

        static Nebula* instance;
        std::optional<ErrorCallback> onError;

        std::unique_ptr<Input> input;

        Vao quadVao;
        Vbo quadVbo;

        Vao cubeVao;
        Vbo cubeVbo;

        std::vector<Light> lights;
    private:
        void initialize();

        static void errorCallback(int error, const char* description);
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        static void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        void update(double deltaTime);
        void draw();

        static std::vector<Light> createLights();
        void setLights(Shader& shader);

        void renderQuad();
        void renderCube();

    public:
        explicit Nebula(NebulaOptions  options);

        void start();

        static Nebula& getInstance();
    };

} // nebula

#endif //NEBULA_MAIN_NEBULA_HPP
