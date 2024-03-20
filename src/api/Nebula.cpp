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
#include "../util/RandomUtils.hpp"
#include "../graphics/RenderingPass.hpp"
#include "../graphics/buffersObjects/RBO.hpp"
#include "../graphics/buffersObjects/GBuffer.hpp"
#include "../ui/UILayer.hpp"
#include "../ui/UIElements/TextElement.hpp"
#include "../ui/UISystem.hpp"
#include "../ui/UIElements/TextureElement.hpp"

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
    Nebula *Nebula::instance;

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

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            Debug::logError("Failed to initialize GLAD");
            exit(EXIT_FAILURE);
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

        glViewport(0, 0, options.width, options.height);

        if (glDebugMessageCallback) {
            glEnable(GL_DEBUG_OUTPUT);
            glDebugMessageCallback(&onDebug, nullptr);
            glEnable(GL_DEBUG_OUTPUT);
        }

        glfwSetFramebufferSizeCallback(window->getWindow(), framebufferResizeCallback);

        registerMeshLoader(std::make_unique<GltbLoader>());

        input = std::make_unique<Input>(window->getWindow());
        camera = std::make_unique<FpsCam>(window->getWindow());
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
        } else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
            enableTexture = !enableTexture;
        }
    }

    std::shared_ptr<Mesh> mesh;

    void Nebula::start() {

//        std::vector<RenderingPass> renderingPasses;
//
//        //mesh = loadMesh(R"(resources/models/bottle/bottle.glb)");
//        mesh = loadMesh(R"(resources/scenes/Test01/Resources/island.glb)");
//        std::unique_ptr<BasicShader> shader = std::make_unique<BasicShader>("resources/simple");
//
//        GBuffer gBuffer = GBuffer(options.width, options.height);
//
//        //position texture
//        gBuffer.addTextureAttachment(GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT0);
//        std::cout << "position tex\n";
//        gBuffer.addTextureAttachment(GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT1);
//        std::cout << "normal tex\n";
//        gBuffer.addTextureAttachment(GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT2);
//        std::cout << "color tex\n";
        //gBuffer.setDrawBuffers({GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2});

//
//
//        Fbo positionBuffer = FBO::create(options.width, options.height);
//        Rbo positionRbo = RBO::create(positionBuffer, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
//        auto positionShader = std::make_unique<BasicShader>("resources/testing/positions");
//        RenderingPass positionPass = RenderingPass(positionBuffer, *positionShader, "position");
//
//        Fbo normalBuffer = FBO::create(options.width, options.height);
//        Rbo normalRbo = RBO::create(normalBuffer, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
//        auto normalShader = std::make_unique<BasicShader>("resources/testing/normals");
//        RenderingPass normalPass = RenderingPass(normalBuffer, *normalShader, "normal");
//
//        Fbo colorBuffer = FBO::create(options.width, options.height);
//        Rbo colorRbo = RBO::create(colorBuffer, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
//        auto colorShader = std::make_unique<BasicShader>("resources/testing/colors");
//        RenderingPass colorPass = RenderingPass(colorBuffer, *colorShader, "color");
//
//        auto outputShader = std::make_unique<BasicShader>("resources/testing/shading");
//        auto lightShader = std::make_unique<BasicShader>("resources/testing/lights");
//
//        UISystem uiSystem = UISystem(window, "#version 400");
//        UILayer debugLayer = UILayer("Texture Debugger");
//        debugLayer.addElement(
//                std::make_unique<TextureElement>(positionPass.getTexture(), options.width / 4, options.height / 4));
//        debugLayer.addElement(
//                std::make_unique<TextureElement>(normalPass.getTexture(), options.width / 4, options.height / 4));
//        debugLayer.addElement(
//                std::make_unique<TextureElement>(colorPass.getTexture(), options.width / 4, options.height / 4));
//
//        uiSystem.addLayer(debugLayer);
//
//        lights = createLights();

        //TODO NOTE: uniforms can only be set on an active shader
       // float rotation = 0;
        auto currentTime = static_cast<double>(glfwGetTime());
        double lastTime = currentTime;
//        Texture specular = Texture(glm::vec4(0.1f, 0, 0, 0));
        while (!glfwWindowShouldClose(window->getWindow())) {

            currentTime = static_cast<double>(glfwGetTime());
            double deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            checkGLError(__FILE__, __LINE__);

            update(deltaTime);



            draw();

//            rotate(model, glm::vec3(rotation, rotation, rotation));
//            //model = glm::scale(model, {5,5,5});
//
//
//            positionPass.render(camera, model, projection, *mesh);
//            normalPass.render(camera, model, projection, *mesh);
//
//            //Set specular texture for now.
//            colorShader->use();
//            colorShader->setUniform("albedo", 0);
//            colorShader->setUniform("specular", 1);
//            specular.bind(1);
//            colorPass.render(camera, model, projection, *mesh);
//            specular.unbind();
//
//            outputShader->use();
//            outputShader->setUniform("positionTex", 0);
//            outputShader->setUniform("normalTex", 1);
//            outputShader->setUniform("albedoTex", 2);
//
//            positionPass.getTexture().bind(0);
//            normalPass.getTexture().bind(1);
//            colorPass.getTexture().bind(2);
//
//            outputShader->setProjectionMatrix(projection);
//            outputShader->setModelMatrix(glm::mat4(1));
//            outputShader->setViewMatrix(camera.getMatrix());
//            outputShader->setUniform("cameraPos", camera.getPosition());
//
//            setLights(*outputShader);
//
//            glDisable(GL_DEPTH_TEST);
//            glClearColor(1, 0.5, 0.5, 1.0f);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//            renderQuad();
//
//            positionBuffer->bind(GL_READ_FRAMEBUFFER);
//            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
//
//            glBlitFramebuffer(0, 0, options.width, options.height, 0, 0, options.width, options.height,
//                              GL_DEPTH_BUFFER_BIT, GL_NEAREST);
//            FBO::unbind();
//
//            lightShader->use();
//            lightShader->setUniform("projection", projection);
//            lightShader->setUniform("view", camera.getMatrix());
//
//            for(int i = 0; i < lights.size(); i++) {
//                model = glm::mat4(1.0f);
//                model = glm::translate(model, lights[i].Position);
//                model = glm::scale(model, glm::vec3(0.125f));
//                lightShader->setUniform("model", model);
//                lightShader->setUniform("lightColor", lights[i].Color);
//                renderCube();
//            }
//
//            uiSystem.render();

            glfwSwapBuffers(window->getWindow());
            glfwPollEvents();
        }

        window = nullptr;
        glfwTerminate();
    }

    void Nebula::update(double deltaTime) {
        // input->update();
        camera->update(deltaTime);

        static bool previousRendererKeyState = false;
        int action = glfwGetKey(window->getWindow(), GLFW_KEY_KP_SUBTRACT);
        if (action == GLFW_PRESS && !previousRendererKeyState) {
            previousRendererKeyState = true;
            swapRenderer();
        } else if (action == GLFW_RELEASE) {
            previousRendererKeyState = false;
        }
    }

    void Nebula::draw() {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        glm::mat4 projection = createPerspective(glm::radians(45.0f),
                                                 static_cast<float>(viewport[2]) / static_cast<float>(viewport[3]),
                                                 0.1f, 100.0f);
        currentRenderer->render(entities, *camera, projection);
    }

    void Nebula::renderQuad() {

        if (!quadVao) {
            std::vector<Vertex> vertices = {
                    Vertex::PT({-1.0f, 1.0f, -0.0f}, {0.0f, 1.0f}),
                    Vertex::PT({-1.0f, -1.0f, -0.0f}, {0.0f, 0.0f}),
                    Vertex::PT({1.0f, 1.0f, -0.0f}, {1.0f, 1.0f}),
                    Vertex::PT({1.0f, -1.0f, -0.0f}, {1.0f, 0.0f})
            };
            quadVao = VAO::create();
            quadVbo = VBO::create(vertices);

            quadVao->bind();
            quadVbo->bind();

            quadVao->addVertexBufferLayout(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
            quadVao->addVertexBufferLayout(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                           (void *) offsetof(Vertex, texcoord));

            quadVao->unbind();
            quadVbo->unbind();
        }
        quadVao->bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        quadVao->unbind();
    }

    void Nebula::renderCube() {
        if (!cubeVao) {
            float verts[] = {
                    // back face
                    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
                    1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
                    1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
                    1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
                    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
                    -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // top-left
                    // front face
                    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
                    1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // bottom-right
                    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
                    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
                    -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top-left
                    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
                    // left face
                    -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
                    -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
                    -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
                    -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
                    -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-right
                    -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
                    // right face
                    1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
                    1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
                    1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
                    1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
                    1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
                    1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
                    // bottom face
                    -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
                    1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
                    1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
                    1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
                    -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
                    -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
                    // top face
                    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
                    1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
                    1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right
                    1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
                    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
                    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f  // bottom-left
            };

            std::vector<Vertex> vertices;

            for (int i = 0; i < sizeof(verts) / sizeof(float); i += 8) {
                vertices.push_back(Vertex::PTN({verts[i], verts[i + 1], verts[i + 2]}, {verts[i + 6], verts[i + 7]},
                                               {verts[i + 3], verts[i + 4], verts[i + 5]}));
            }

            cubeVao = VAO::create();
            cubeVbo = VBO::create(vertices);

            cubeVao->bind();
            cubeVbo->bind();

            cubeVao->addVertexBufferLayout(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                           (void *) offsetof(Vertex, position));
            cubeVao->addVertexBufferLayout(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                           (void *) offsetof(Vertex, normal));
            cubeVao->addVertexBufferLayout(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                           (void *) offsetof(Vertex, texcoord));

            cubeVao->unbind();
            cubeVbo->unbind();
        }

        cubeVao->bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);
        cubeVao->unbind();
    }

    std::vector<Light> Nebula::createLights() {
        std::vector<Light> lights;

//        Light light;
//        auto xPos = 0;
//        auto yPos = 2;
//        auto zPos = 0;
//        light.Position = glm::vec3(xPos, yPos, zPos);
//
//        auto rColor = 0.5f;
//        auto gColor = 0.3f;
//        auto bColor = 0.01f;
//        light.Color = glm::vec3(rColor, gColor, bColor);
//        lights.push_back(light);
        for(int i = 0; i < NR_LIGHTS; i++) {
            Light light;

            auto xPos = static_cast<float>(((RandomUtils::RandomUtils::GetInstance()->generateInt(0, 100)) / 100.0) * 6.0 - 3.0);
            auto yPos = static_cast<float>(((RandomUtils::RandomUtils::GetInstance()->generateInt(0, 100)) / 100.0) * 6.0 - 4.0);
            auto zPos = static_cast<float>(((RandomUtils::RandomUtils::GetInstance()->generateInt(0, 100)) / 100.0) * 6.0 - 3.0);
            light.Position = glm::vec3(xPos, yPos, zPos);

            auto rColor = static_cast<float>(((rand() % 100) / 200.0f));// + 0.5); // between 0.5 and 1.)
            auto gColor = static_cast<float>(((rand() % 100) / 200.0f));// + 0.5); // between 0.5 and 1.)
            auto bColor = static_cast<float>(((rand() % 100) / 200.0f));// + 0.5); // between 0.5 and 1.)
            light.Color = glm::vec3(rColor, gColor, bColor);


            lights.push_back(light);
        }

        return lights;
    }

    void Nebula::setLights(Shader &shader) {
        for (int i = 0; i < lights.size(); i++) {
            shader.setUniform("lights[" + std::to_string(i) + "].Position", lights[i].Position);
            shader.setUniform("lights[" + std::to_string(i) + "].Color", lights[i].Color);

            const float constant = 1.0f; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
            const float linear = 0.7f;
            const float quadratic = 1.8f;

            shader.setUniform("lights[" + std::to_string(i) + "].Linear", linear);
            shader.setUniform("lights[" + std::to_string(i) + "].Quadratic", quadratic);

            const float maxBrightness = std::fmaxf(std::fmaxf(lights[i].Color.r, lights[i].Color.g), lights[i].Color.b);
            float radius = (-linear +
                            std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) /
                           (2.0f * quadratic);
            shader.setUniform("lights[" + std::to_string(i) + "].Radius", radius);
        }
    }

//    void Nebula::setRenderer(std::shared_ptr<Renderer> renderer) {
//        //this->renderer = std::move(renderer);
//    }

    void Nebula::addEntity(Entity &entity) {
        entities.push_back(entity);
    }

    const std::unique_ptr<Window> &Nebula::getWindow() const {
        return window;
    }

    void Nebula::addRenderer(std::shared_ptr<Renderer> renderer) {
        renderers.push_back(renderer);
        currentRenderer = renderer;
        currentRendererIndex = renderers.size() - 1;
    }

    void Nebula::swapRenderer() {
        if(currentRendererIndex + 1 >= renderers.size()) {
            currentRendererIndex = 0;
        } else {
            currentRendererIndex++;
        }

        currentRenderer = renderers[currentRendererIndex];
    }
} // nebula