//
// Created by Jasper on 12/24/2023.
//

#include <utility>

//include glad before glfw
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

#include "Nebula.hpp"

#include "../util/Debug.hpp"

#include "../shaders/BasicShader.hpp"

#include "../graphics/FpsCam.hpp"

#include "../util/math.hpp"
#include "../graphics/material/Texture.hpp"
#include "../graphics/buffersObjects/VBO.hpp"
#include "../graphics/mesh/Mesh.hpp"
#include "../graphics/mesh/MeshLoading.hpp"
#include "../graphics/mesh/loaders/GltbLoader.hpp"
#include "../util/glUtil.hpp"

#ifdef WIN32

void GLAPIENTRY onDebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                        const void *userParam)
#else
void onDebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                        GLvoid *userParam)
#endif
{
    nebula::Debug::logError(message);
}

namespace nebula {
    Nebula* Nebula::instance;

    Nebula::Nebula(NebulaOptions options) : options(std::move(options)) {
        if (instance) {
            throw std::runtime_error("Nebula was already initialized");
        }

        instance = this;
        initialize();
    }

    Nebula &Nebula::getInstance() {
        if (!instance) {
            throw std::runtime_error("Nebula was not initialized");
        }

        return *instance;
    }

    void Nebula::initialize() {
        glfwSetErrorCallback(errorCallback);

        if (!glfwInit()) {
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = std::make_unique<Window>(options);

        if (!window) {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetKeyCallback(window->getWindow(), onKeyCallback);
        glfwMakeContextCurrent(window->getWindow());
        glfwSwapInterval(1);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            Debug::logError("Failed to initialize GLAD");
            exit(EXIT_FAILURE);
        }

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        //glEnable(GL_BLEND);

        glViewport(0, 0, options.width, options.height);

        //if(glDebugMessageCallback) {
        //glEnable(GL_DEBUG_OUTPUT);
        //glDebugMessageCallback(&onDebug, nullptr);
            //glEnable(GL_DEBUG_OUTPUT);
        //}

        glfwSetFramebufferSizeCallback(window->getWindow(), framebufferResizeCallback);

        registerMeshLoader(std::make_unique<GltbLoader>());
    }

    void Nebula::errorCallback(int error, const char *description) {
        Nebula &nebulaInstance = Nebula::getInstance();

        if (!nebulaInstance.onError) {
            return;
        }

        nebulaInstance.onError.value()(error, description);
    }

    void Nebula::framebufferResizeCallback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }
    bool enableTexture = true;
    void Nebula::onKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        } else if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
            enableTexture = !enableTexture;
        }
    }

    void Nebula::start() {

        FpsCam camera(window->getWindow());

        std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>("resources/simple");
        shader->use();

        auto mesh = loadMesh(R"(resources/models/bottle/bottle.glb)");

        float rotation = 0;
        auto currentTime = static_cast<float>(glfwGetTime());
        float lastTime = currentTime;
        while (!glfwWindowShouldClose(window->getWindow())) {

            currentTime = static_cast<float>(glfwGetTime());
            float deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                // Print or handle the error
                std::cout << "Got an error: " << error << "\n";
            }

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader->use();

            //projection
            int viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            glm::mat4 projection = createPerspective(glm::radians(45.0f), static_cast<float>(viewport[2]) / static_cast<float>(viewport[3]), 0.1f, 100.0f);
            shader->setProjectionMatrix(projection);

            //view
            camera.update(deltaTime);
            shader->setViewMatrix(camera.getMatrix());
            //model/world
            glm::mat4 model = glm::mat4(1);
            rotate(model, glm::vec3(rotation,rotation,rotation));
            shader->setModelMatrix(model);

            shader->setUniform("time", static_cast<float>(glfwGetTime()));

            mesh->draw(*shader);

            //rotation += 0.5f;
            glfwSwapBuffers(window->getWindow());
            glfwPollEvents();
        }

        window = nullptr;
        glfwTerminate();
    }
} // nebula