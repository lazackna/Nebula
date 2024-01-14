//
// Created by Jasper on 12/24/2023.
//

#include <utility>
#include <glad/glad.h>
#include <iostream>

#include "Nebula.hpp"

#include "../util/Debug.hpp"

#include "../shaders/BasicShader.hpp"
#include "../graphics/Graphics.hpp"

#include "../graphics/FpsCam.hpp"

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

    std::vector<Vertex> createCube() {
        std::vector<Vertex> vertexes;
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, -0.5), glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1, 0), glm::vec3(0, 1, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, -0.5), glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec2(0, 0), glm::vec3(0, 1, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, 0.5), glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(0, 1), glm::vec3(0, 1, 0)));
//
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, -0.5), glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1, 0), glm::vec3(0, 1, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, 0.5), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1, 1), glm::vec3(0, 1, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, 0.5), glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(0, 1), glm::vec3(0, 1, 0)));
//
//        //bottom
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, 0.5), glm::vec4(1.0, 0.0, 1.0, 1.0), glm::vec2(1, 0), glm::vec3(0, -1, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, 0.5), glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec2(0, 0), glm::vec3(0, -1, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, -0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(0, -1, 0)));
//
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, 0.5), glm::vec4(1.0, 0.0, 1.0, 1.0), glm::vec2(1, 0), glm::vec3(0, -1, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, -0.5), glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1, 1), glm::vec3(0, -1, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, -0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(0, -1, 0)));
//
//        //back
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, 0.5), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1, 0), glm::vec3(0, 0, -1)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, 0.5), glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(0, 0), glm::vec3(0, 0, -1)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, 0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(0, 0, -1)));
//
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, 0.5), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1, 0), glm::vec3(0, 0, -1)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, 0.5), glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1, 1), glm::vec3(0, 0, -1)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, 0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(0, 0, -1)));

        //front
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, -0.5), glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1, 0), glm::vec3(0, 0, 1)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, -0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 0), glm::vec3(0, 0, 1)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, -0.5), glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(0, 0, 1)));

        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, -0.5), glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1, 0), glm::vec3(0, 0, 1)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, -0.5), glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1, 1), glm::vec3(0, 0, 1)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, -0.5), glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(0, 0, 1)));

//        //left
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, 0.5), glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(1, 0), glm::vec3(-1, 0, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, -0.5), glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec2(0, 0), glm::vec3(-1, 0, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, -0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(-1, 0, 0)));
//
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, 0.5), glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(1, 0), glm::vec3(-1, 0, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, 0.5), glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec2(1, 1), glm::vec3(-1, 0, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, -0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(-1, 0, 0)));
//
//        //right
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, -0.5), glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1, 0), glm::vec3(1, 0, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, 0.5), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0, 0), glm::vec3(1, 0, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, 0.5), glm::vec4(1.0, 0.0, 1.0, 1.0), glm::vec2(0, 1), glm::vec3(1, 0, 0)));
//
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, -0.5), glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1, 0), glm::vec3(1, 0, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, -0.5), glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1, 1), glm::vec3(1, 0, 0)));
//        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, 0.5), glm::vec4(1.0, 0.0, 1.0, 1.0), glm::vec2(0, 1), glm::vec3(1, 0, 0)));

        return vertexes;
    }

    void Nebula::start() {

        FpsCam camera(window->getWindow());

        std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>("resources/simple");

        shader->use();
        auto vbo = nebula::createVbo(createCube());
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
        camera.setPosition(glm::vec3(0,0,-10));
        while (!glfwWindowShouldClose(window->getWindow())) {

            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                // Print or handle the error
                std::cout << "Got an error: " << error << "\n";
            }

            glClearColor(1, 1, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            int viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            glm::mat4 projection = glm::perspective(glm::radians(75.0f), static_cast<float>(viewport[2]) / static_cast<float>(viewport[3]), 0.01f, 400.0f);
            glm::mat4 view = camera.getMatrix();
            glm::mat4 model = glm::mat4(1);

            glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view * model)));

            //model = glm::translate(model, glm::vec3(0.05,0,0.1));

            shader->use();
            shader->setModelMatrix(model);
            shader->setViewMatrix(view);
            shader->setProjectionMatrix(projection);
            shader->setNormalMatrix(normalMatrix);

            drawVertices(GL_TRIANGLES, vbo);

           // glBindVertexArray(VAO);
//            //shader.setUniform("a_position", glm::vec3(-0.3,0.4,10));
//            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//            glDrawArrays(GL_TRIANGLES)

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