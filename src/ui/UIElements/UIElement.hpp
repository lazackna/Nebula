//
// Created by Jasper on 2/9/2024.
//

#ifndef NEBULA_MAIN_UIELEMENT_HPP
#define NEBULA_MAIN_UIELEMENT_HPP

#include <utility>
#include <string>
#include "imgui.h"

class UIElement {
protected:
    explicit UIElement() = default;
public:
    virtual ~UIElement() = default;

    virtual void render() = 0;
};

#endif //NEBULA_MAIN_UIELEMENT_HPP
