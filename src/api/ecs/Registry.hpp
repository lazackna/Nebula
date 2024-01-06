//
// Created by User on 1/6/2024.
//

#ifndef NEBULA_MAIN_REGISTRY_HPP
#define NEBULA_MAIN_REGISTRY_HPP

#include <memory>
#include <vector>

#include "GameObject.hpp"

namespace nebula {

    class Registry {
        std::vector<std::shared_ptr<GameObject>> gameObjects;
    public:
        std::weak_ptr<GameObject> createGameObject();
    };

} // nebula

#endif //NEBULA_MAIN_REGISTRY_HPP
