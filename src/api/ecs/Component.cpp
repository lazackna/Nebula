//
// Created by User on 1/6/2024.
//

#include "Component.hpp"

#include "GameObject.hpp"

namespace nebula {
    bool Component::isActive() const {
        return active;
    }

    void Component::setActive(bool active) {
        this->active = active;
    }

    void Component::setOwner(const std::shared_ptr<GameObject> &owner) {
        gameObject = owner;
    }

    std::weak_ptr<GameObject> Component::getGameObject() {
        return gameObject;
    }
} // nebula