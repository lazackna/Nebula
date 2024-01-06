//
// Created by User on 1/6/2024.
//

#ifndef NEBULA_MAIN_COMPONENT_HPP
#define NEBULA_MAIN_COMPONENT_HPP

#include <memory>

namespace nebula {

    class GameObject;

    class Component {
    private:
        friend class GameObject;

        std::weak_ptr<GameObject> gameObject;

        bool active = true;
    public:
        virtual ~Component() = default;

        void setActive(bool active);

        bool isActive() const;

        std::weak_ptr<GameObject> getGameObject();
    private:
        void setOwner(const std::shared_ptr<GameObject>& owner);
    };

} // nebula

#endif //NEBULA_MAIN_COMPONENT_HPP
