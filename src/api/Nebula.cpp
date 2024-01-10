//
// Created by Jasper on 12/24/2023.
//

#include <utility>
#include <glad/glad.h>

#include "Nebula.hpp"

//#include "../Window.hpp"
#include "../util/Debug.hpp"

#include "../graphics/Shader.hpp"
#include "../graphics/Graphics.hpp"
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

        //glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

        glViewport(0, 0, options.width, options.height);

        if(glDebugMessageCallback) {
            glDebugMessageCallback(&onDebug, nullptr);
            glEnable(GL_DEBUG_OUTPUT);
        }

        glfwSetFramebufferSizeCallback(window->getWindow(), framebufferResizeCallback);
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

    void Nebula::onKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    void Nebula::start() {
        Shader shader = Shader("simple");

        shader.use();
        nebula::createVbo()
//        float vertices[] = {
//                0.5f,  0.5f, 0.0f,  // top right
//                0.5f, -0.5f, 0.0f,  // bottom right
//                -0.5f, -0.5f, 0.0f,  // bottom left
//                -0.5f,  0.5f, 0.0f   // top left
//        };
//
//        unsigned int indices[] = {  // note that we start from 0!
//                0, 1, 3,  // first Triangle
//                1, 2, 3   // second Triangle
//        };
//
//        unsigned int VBO, VAO, EBO;
//
//        glGenVertexArrays(1, &VAO);
//        glGenBuffers(1, &VBO);
//        glGenBuffers(1, &EBO);
//
//        glBindVertexArray(VAO);
//
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
//        glEnableVertexAttribArray(0);
//
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glBindVertexArray(0);

        while (!glfwWindowShouldClose(window->getWindow())) {

            glClearColor(1, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.use();

            //glBindVertexArray(VAO);
            //shader.setUniform("a_position", glm::vec3(-0.3,0.4,10));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(window->getWindow());
            glfwPollEvents();
        }

//        glDeleteVertexArrays(1, &VAO);
//        glDeleteBuffers(1, &VBO);
//        glDeleteBuffers(1, &EBO);
        //glDeleteProgram(shaderProgram);

        window = nullptr;
        glfwTerminate();
    }
} // nebula