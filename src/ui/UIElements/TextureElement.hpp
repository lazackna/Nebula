//
// Created by Jasper on 2/9/2024.
//

#ifndef NEBULA_MAIN_TEXTUREELEMENT_HPP
#define NEBULA_MAIN_TEXTUREELEMENT_HPP

#include "UIElement.hpp"
#include "../../graphics/material/Texture.hpp"

namespace nebula {

    class TextureElement : public UIElement {
        Texture& texture;
        ImVec2 size;
    public:
        explicit TextureElement(Texture& texture, float width, float height);
        void render() override;
    };

} // nebula

#endif //NEBULA_MAIN_TEXTUREELEMENT_HPP
