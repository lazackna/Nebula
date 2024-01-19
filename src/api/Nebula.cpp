//
// Created by Jasper on 12/24/2023.
//

#include <utility>
#include <glad/glad.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Nebula.hpp"

#include "../util/Debug.hpp"

#include "../shaders/BasicShader.hpp"
#include "../graphics/Graphics.hpp"

#include "../graphics/FpsCam.hpp"

#include "../util/math.hpp"
#include "../graphics/Texture.hpp"
#include "../graphics/VBO.hpp"

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
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, -0.5), glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1, 0), glm::vec3(0, 1, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, -0.5), glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec2(0, 0), glm::vec3(0, 1, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, 0.5), glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(0, 1), glm::vec3(0, 1, 0)));

        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, -0.5), glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1, 0), glm::vec3(0, 1, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, 0.5), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1, 1), glm::vec3(0, 1, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, 0.5), glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(0, 1), glm::vec3(0, 1, 0)));

        //bottom
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, 0.5), glm::vec4(1.0, 0.0, 1.0, 1.0), glm::vec2(1, 0), glm::vec3(0, -1, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, 0.5), glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec2(0, 0), glm::vec3(0, -1, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, -0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(0, -1, 0)));

        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, 0.5), glm::vec4(1.0, 0.0, 1.0, 1.0), glm::vec2(1, 0), glm::vec3(0, -1, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, -0.5), glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1, 1), glm::vec3(0, -1, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, -0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(0, -1, 0)));

        //back
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, 0.5), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1, 0), glm::vec3(0, 0, -1)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, 0.5), glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(0, 0), glm::vec3(0, 0, -1)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, 0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(0, 0, -1)));

        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, 0.5), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1, 0), glm::vec3(0, 0, -1)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, 0.5), glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1, 1), glm::vec3(0, 0, -1)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, 0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(0, 0, -1)));

        //front
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, -0.5), glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1, 0), glm::vec3(0, 0, 1)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, -0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 0), glm::vec3(0, 0, 1)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, -0.5), glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(0, 0, 1)));

        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, -0.5), glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1, 0), glm::vec3(0, 0, 1)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, -0.5), glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1, 1), glm::vec3(0, 0, 1)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, -0.5), glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(0, 0, 1)));

        //left
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, 0.5), glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(1, 0), glm::vec3(-1, 0, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, -0.5), glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec2(0, 0), glm::vec3(-1, 0, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, -0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(-1, 0, 0)));

        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, 0.5, 0.5), glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(1, 0), glm::vec3(-1, 0, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, 0.5), glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec2(1, 1), glm::vec3(-1, 0, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(-0.5, -0.5, -0.5), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0, 1), glm::vec3(-1, 0, 0)));

        //right
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, -0.5), glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1, 0), glm::vec3(1, 0, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, 0.5), glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(0, 0), glm::vec3(1, 0, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, 0.5), glm::vec4(1.0, 0.0, 1.0, 1.0), glm::vec2(0, 1), glm::vec3(1, 0, 0)));

        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, 0.5, -0.5), glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1, 0), glm::vec3(1, 0, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, -0.5), glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1, 1), glm::vec3(1, 0, 0)));
        vertexes.push_back(Vertex::PCTN(glm::vec3(0.5, -0.5, 0.5), glm::vec4(1.0, 0.0, 1.0, 1.0), glm::vec2(0, 1), glm::vec3(1, 0, 0)));

        return vertexes;
    }

    void Nebula::start() {

        FpsCam camera(window->getWindow());

        std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>("resources/simple");
        //auto shader = std::make_unique<Shader>("resources/base");
        shader->use();

        float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f,  0.5f, 0.0f
        };

        std::vector<Vertex> vertexes = createCube();

//        for(int i = 0; i < 3; i++) {
//            vertexes.push_back(Vertex::P(glm::vec3(vertices[0 + 3 * i], vertices[1 + 3 * i], vertices[2 + 3 * i])));
//        }

        //auto vao = createVao(vertexes);
        //GLuint vbo;//, vao;
       // glGenBuffers(1, &vbo);
       // glGenVertexArrays(1, &vao);

        //glBindVertexArray(vao);

//        glBindBuffer(GL_ARRAY_BUFFER, vbo);
//        glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(Vertex), &vertexes[0], GL_STATIC_DRAW);
        Vao vao = std::make_unique<VAO>();
        vao->bind();
        Vbo vbo = std::make_unique<VBO>(vertexes);
        vbo->bind();

        vao->addVertexBufferLayout(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
        vao->addVertexBufferLayout(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));
        vao->addVertexBufferLayout(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texcoord));
        vao->addVertexBufferLayout(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, color));


        Texture texture = Texture("tex.png");

        float rotation = 0;

        float currentTime = static_cast<float>(glfwGetTime());
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

            int viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
            glm::mat4 model = glm::mat4(1);

            rotate(model, glm::vec3(rotation,rotation,rotation));
            //model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
            //model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
            shader->setProjectionMatrix(projection);

            camera.update(deltaTime);
            glm::mat4 view = glm::mat4(1);
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            shader->setViewMatrix(camera.getMatrix());
            shader->setModelMatrix(model);

            texture.bind();

            vao->bind();
            glDrawArrays(GL_TRIANGLES, 0, vertexes.size());
            vao->unbind();

            rotation += 0.5f;
            glfwSwapBuffers(window->getWindow());
            glfwPollEvents();
        }

//        glDeleteVertexArrays(1, &VAO);
//        glDeleteBuffers(1, &VAO);
//        glDeleteBuffers(1, &EBO);
        //glDeleteProgram(shaderProgram);

        window = nullptr;
        glfwTerminate();
    }
} // nebula