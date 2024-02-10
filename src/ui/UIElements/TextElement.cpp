//
// Created by Jasper on 2/9/2024.
//

#include "TextElement.hpp"

#include <utility>

namespace nebula {
    void TextElement::render() {
        ImGui::Text(text.c_str());
    }

    TextElement::TextElement(const std::string &name, std::string text) : text(std::move(text)) {

    }
} // nebula