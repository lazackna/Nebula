//
// Created by Jasper on 2/9/2024.
//

#ifndef NEBULA_MAIN_UISYSTEM_HPP
#define NEBULA_MAIN_UISYSTEM_HPP

#include "../Window.hpp"
#include "UILayer.hpp"

namespace nebula {

    class UISystem {
        std::vector<UILayer> layers;
    public:
        UISystem(const std::unique_ptr<Window>& window, const std::string& version);
        ~UISystem();

        void addLayer(UILayer &layer);
        void render();
    };

} // nebula

#endif //NEBULA_MAIN_UISYSTEM_HPP
