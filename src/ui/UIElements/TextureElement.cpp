//
// Created by Jasper on 2/9/2024.
//

#include "TextureElement.hpp"

namespace nebula {
    void TextureElement::render() {
        ImGui::Image((void*)(intptr_t)texture.getTextureId(), size, ImVec2(0, 0), ImVec2(1, -1));
    }

    TextureElement::TextureElement(Texture &texture, float width, float height) : texture(texture), size(width, height) {

    }
} // nebula