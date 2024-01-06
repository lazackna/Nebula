//
// Created by User on 1/6/2024.
//

#include "Registry.hpp"

namespace nebula {
    std::weak_ptr<GameObject> Registry::createGameObject() {
        gameObjects.push_back(std::make_shared<GameObject>());

        return gameObjects.back();
    }
} // nebula