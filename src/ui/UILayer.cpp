//
// Created by Jasper on 2/9/2024.
//

#include "UILayer.hpp"

#include <utility>

namespace nebula {

    void UILayer::render() const{

        ImGui::Begin(name.c_str());

        for(const auto& element : elements) {
            element->render();
        }

        ImGui::End();
    }

    UILayer::UILayer(std::string  name) : name(std::move(name)) {

    }
} // nebula