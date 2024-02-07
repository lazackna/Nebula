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

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

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

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
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
        //glDepthFunc(GL_LESS);
        //glEnable(GL_BLEND);

        glViewport(0, 0, options.width, options.height);

        if(glDebugMessageCallback) {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(&onDebug, nullptr);
            glEnable(GL_DEBUG_OUTPUT);
        }

        glfwSetFramebufferSizeCallback(window->getWindow(), framebufferResizeCallback);

        registerMeshLoader(std::make_unique<GltbLoader>());


        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);

        ImGui_ImplOpenGL3_Init("#version 400");

        input = std::make_unique<Input>(window->getWindow());
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
    std::shared_ptr<Mesh> mesh;
    void Nebula::start() {

        FpsCam camera(window->getWindow());

        mesh = loadMesh(R"(resources/models/bottle/bottle.glb)");
        std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>("resources/simple");
        //shader->use();


        Fbo colorBuffer = FBO::create(options.width, options.height);
        auto colorShader = std::make_unique<BasicShader>("resources/pbr/colors");
        colorShader->use();
        Texture collorBufferTexture = Texture(colorBuffer);
//        Fbo normalBuffer = FBO::create(options.width, options.height);
//        Texture normalBufferTexture = Texture(normalBuffer);
//        auto normalShader = std::make_unique<BasicShader>("resources/pbr/normals");
//
//        Fbo objectBuffer = FBO::create(options.width, options.height);
//        Texture objectBufferTexture = Texture(objectBuffer);
//        auto objectShader = std::make_unique<BasicShader>("resources/pbr/object");

        float rotation = 0;
        auto currentTime = static_cast<double>(glfwGetTime());
        double lastTime = currentTime;
        while (!glfwWindowShouldClose(window->getWindow())) {

            currentTime = static_cast<double>(glfwGetTime());
            double deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                // Print or handle the error
                std::cout << "Got an error: " << error << "\n";
            }

            update(deltaTime);
            draw();

            colorBuffer->bind();
            //projection
            int viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            glm::mat4 projection = createPerspective(glm::radians(45.0f), static_cast<float>(viewport[2]) / static_cast<float>(viewport[3]), 0.1f, 100.0f);
            shader->setProjectionMatrix(projection);
            colorShader->setProjectionMatrix(projection);
            //normalShader->setProjectionMatrix(projection);
            //objectShader->setProjectionMatrix(projection);
            //view
            camera.update(deltaTime);
            shader->setViewMatrix(camera.getMatrix());
            colorShader->setViewMatrix(camera.getMatrix());
            //normalShader->setViewMatrix(camera.getMatrix());
            //objectShader->setViewMatrix(camera.getMatrix());
            //model/world
            glm::mat4 model = glm::mat4(1);
            rotate(model, glm::vec3(rotation,rotation,rotation));
            shader->setModelMatrix(model);
            colorShader->setModelMatrix(model);
            //normalShader->setModelMatrix(model);
            //objectShader->setModelMatrix(model);

            //colorBuffer->bind();
            glEnable(GL_DEPTH_TEST);
            glClearColor(0., 0., 0., 0.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            mesh->draw(*colorShader);
            colorBuffer->unbind();


//            normalBuffer->bind();
//            glEnable(GL_DEPTH_TEST);
//            glClearColor(0., 0., 0., 0.f);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            mesh->draw(*normalShader);
//            normalBuffer->unbind();
//
//            objectBuffer->bind();
//            glEnable(GL_DEPTH_TEST);
//            glClearColor(0., 0., 0., 0.f);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            mesh->draw(*objectShader);
//            objectBuffer->unbind();


            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            mesh->draw(*shader);

//            if(input->getKey(GLFW_KEY_P)) {
//                std::cout << "P\n";
//            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("BufferInspector");
            ImGui::SetWindowSize({static_cast<float>(options.width / 4) + 20, static_cast<float>(options.height / 4) + 20});
            ImGui::Text("%s","ColorBuffer");
            ImGui::Image((void*)(intptr_t)collorBufferTexture.getTextureId(), ImVec2(options.width / 4, options.height / 4), ImVec2(0, 0), ImVec2(1, -1));
            //ImGui::Image((void*)(intptr_t)normalBufferTexture.getTextureId(), ImVec2(options.width / 4, options.height / 4), ImVec2(0, 0), ImVec2(1, -1));
            //ImGui::Image((void*)(intptr_t)objectBufferTexture.getTextureId(), ImVec2(options.width / 4, options.height / 4), ImVec2(0, 0), ImVec2(1, -1));
            ImGui::End();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window->getWindow());
            glfwPollEvents();
        }

        window = nullptr;
        glfwTerminate();
    }

    void Nebula::update(double deltaTime) {
       // input->update();
    }

    void Nebula::draw() {

    }
} // nebula