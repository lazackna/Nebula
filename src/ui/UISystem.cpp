//
// Created by Jasper on 2/9/2024.
//

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "UISystem.hpp"

namespace nebula {
    UISystem::UISystem(const std::unique_ptr<Window> &window, const std::string &version) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
        ImGui_ImplOpenGL3_Init(version.c_str());
    }

    UISystem::~UISystem() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void UISystem::addLayer(UILayer &layer) {
        layers.push_back(std::move(layer));
    }

    void UISystem::render() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for(const auto& layer : layers) {
            layer.render();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
} // nebula