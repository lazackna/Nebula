//
// Created by Jasper on 2/9/2024.
//

#ifndef NEBULA_MAIN_UILAYER_HPP
#define NEBULA_MAIN_UILAYER_HPP

#include <memory>
#include <vector>

#include "UIElements/UIElement.hpp"
#include "../Window.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace nebula {

    class UILayer {
        std::vector<std::unique_ptr<UIElement>> elements;
        std::string name;
    public:
        explicit UILayer(std::string name);

        void addElement(std::unique_ptr<UIElement> element) {
            elements.push_back(std::move(element));
        }

        void render() const;
    };

} // nebula

#endif //NEBULA_MAIN_UILAYER_HPP
