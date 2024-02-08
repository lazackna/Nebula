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
#include "../graphics/RenderingPass.hpp"
#include "../graphics/buffersObjects/RBO.hpp"
#include "../graphics/buffersObjects/GBuffer.hpp"

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
        glEnable(GL_BLEND);

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

        std::vector<RenderingPass> renderingPasses;

        mesh = loadMesh(R"(resources/models/cube/cube.glb)");
        std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>("resources/simple");
//        std::unique_ptr<BasicShader> gBufferShader = std::make_unique<BasicShader>("resources/deferred/gBuffer");

        auto geometryPassShader = std::make_unique<BasicShader>("resources/deferred/gBuffer");
        auto lightingPassShader = std::make_unique<BasicShader>("resources/deferred/gBuffer");
        auto lightBoxShader = std::make_unique<BasicShader>("resources/deferred/gBuffer");

//        Fbo positionBuffer = FBO::create(options.width, options.height);
//        Rbo positionRbo = RBO::create(positionBuffer, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
//        auto positionShader = std::make_unique<BasicShader>("resources/deferred/positions");
//        RenderingPass positionPass = RenderingPass(positionBuffer, *positionShader, "position");
//
//        Fbo normalBuffer = FBO::create(options.width, options.height);
//        Rbo normalRbo = RBO::create(normalBuffer, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
//        auto normalShader = std::make_unique<BasicShader>("resources/deferred/normals");
//        RenderingPass normalPass = RenderingPass(normalBuffer, *normalShader, "normal");
//
//        Fbo colorBuffer = FBO::create(options.width, options.height);
//        Rbo colorRbo = RBO::create(colorBuffer, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
//        auto colorShader = std::make_unique<BasicShader>("resources/deferred/colors");
//        RenderingPass colorPass = RenderingPass(colorBuffer, *colorShader, "color");

        GBuffer gBuffer = GBuffer(options.width, options.height);
        std::cout << "here\n";
        gBuffer.addTextureAttachment(GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT0, "position");
        std::cout << "here1\n";
        gBuffer.addTextureAttachment(GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT1, "normal");
        std::cout << "here2\n";
        gBuffer.addTextureAttachment(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_COLOR_ATTACHMENT2, "albedoSpecular");
        std::cout << "here3\n";
        //gBuffer.addRenderBuffer(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
        std::cout << "here4\n";
        gBuffer.unbind();
        GLenum error = glGetError();

        //Currently throws error because it doesn't exist
        lightingPassShader->use();
        lightingPassShader->setUniform("gPosition", 0);
        lightingPassShader->setUniform("gNormal", 1);
        lightingPassShader->setUniform("gAlbedoSpec", 2);

        //TODO NOTE: uniforms can only be set on an active shader
        float rotation = 0;
        auto currentTime = static_cast<double>(glfwGetTime());
        double lastTime = currentTime;
        while (!glfwWindowShouldClose(window->getWindow())) {

            currentTime = static_cast<double>(glfwGetTime());
            double deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            checkGLError(__FILE__, __LINE__);

            update(deltaTime);
            draw();

            camera.update(deltaTime);

            //projection
            int viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            glm::mat4 projection = createPerspective(glm::radians(45.0f), static_cast<float>(viewport[2]) / static_cast<float>(viewport[3]), 0.1f, 100.0f);
            glm::mat4 model = glm::mat4(1);
            rotate(model, glm::vec3(rotation,rotation,rotation));



//            positionPass.render(camera, model, projection, *mesh);
//            normalPass.render(camera, model, projection, *mesh);
//            colorPass.render(camera, model, projection, *mesh);

//            normalShader->use();
//            normalShader->setProjectionMatrix(projection);
//            normalShader->setViewMatrix(camera.getMatrix());
//            normalShader->setModelMatrix(model);
//            normalBuffer->bind();
//            glEnable(GL_DEPTH_TEST);
//            glClearColor(0., 0., 0., 0.f);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            mesh->draw(*normalShader);
//            normalBuffer->unbind();
//
//            colorShader->use();
//            colorShader->setProjectionMatrix(projection);
//            colorShader->setViewMatrix(camera.getMatrix());
//            colorShader->setModelMatrix(model);
//            colorBuffer->bind();
//            glEnable(GL_DEPTH_TEST);
//            glClearColor(0., 0., 0., 0.f);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            mesh->draw(*colorShader);
//            colorBuffer->unbind();
//
//
//            gBufferShader->use();
//            gBufferShader->setProjectionMatrix(projection);
//            gBufferShader->setViewMatrix(camera.getMatrix());
//            gBufferShader->setModelMatrix(model);
//            gBuffer.bind();
//            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//            glEnable(GL_DEPTH_TEST);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            mesh->draw(*gBufferShader);
//            gBuffer.unbind();

            shader->use();
            shader->setProjectionMatrix(projection);
            shader->setViewMatrix(camera.getMatrix());
            shader->setModelMatrix(model);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            mesh->draw(*shader);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("ColorInspector");
            ImGui::SetWindowSize({static_cast<float>(options.width / 4) + 20, static_cast<float>(options.height) - 100});
            auto& textures = gBuffer.getTextureAttachments();
//
            for(auto& tex : textures) {
                ImGui::Image((void*)(intptr_t)tex.texture->getTextureId(), ImVec2(options.width / 4, options.height / 4), ImVec2(0, 0), ImVec2(1, -1));
            }
//            ImGui::Image((void*)(intptr_t)positionPass.getTexture().getTextureId(), ImVec2(options.width / 4, options.height / 4), ImVec2(0, 0), ImVec2(1, -1));
//            //ImGui::End();
//            //ImGui::Begin("NormalInspector");
//            ImGui::Image((void*)(intptr_t)normalPass.getTexture().getTextureId(), ImVec2(options.width / 4, options.height / 4), ImVec2(0, 0), ImVec2(1, -1));
//            //ImGui::End();
//            //ImGui::Begin("ObjectInspector");
//            ImGui::Image((void*)(intptr_t)colorPass.getTexture().getTextureId(), ImVec2(options.width / 4, options.height / 4), ImVec2(0, 0), ImVec2(1, -1));
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