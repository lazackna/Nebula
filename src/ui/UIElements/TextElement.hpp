//
// Created by Jasper on 2/9/2024.
//

#ifndef NEBULA_MAIN_TEXTELEMENT_HPP
#define NEBULA_MAIN_TEXTELEMENT_HPP

#include <string>
#include "UIElement.hpp"

namespace nebula {

    class TextElement : public UIElement {
        std::string text;
    public:
        explicit TextElement(const std::string &name, std::string  text);

        void render() override;
    };

} // nebula

#endif //NEBULA_MAIN_TEXTELEMENT_HPP
