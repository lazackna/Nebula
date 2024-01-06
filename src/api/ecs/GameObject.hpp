//
// Created by User on 1/6/2024.
//

#ifndef NEBULA_MAIN_GAMEOBJECT_HPP
#define NEBULA_MAIN_GAMEOBJECT_HPP

#include <memory>
#include <vector>

#include "Component.hpp"

namespace nebula {

    class Registry;

    class GameObject : public std::enable_shared_from_this<GameObject> {
        friend class Registry;

        std::vector<std::shared_ptr<Component>> components;

    public:
        GameObject() = default;
        template<typename T, typename... TArgs>
        requires std::is_base_of_v<Component, T>
        std::weak_ptr<T> addComponent(TArgs... args) {
            auto component = std::make_shared<T>(args...);
            components.emplace_back(component);
            component->setOwner(shared_from_this());
            return std::dynamic_pointer_cast<T>(component);
        }
    };

} // nebula

#endif //NEBULA_MAIN_GAMEOBJECT_HPP
