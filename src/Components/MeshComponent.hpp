//
// Created by Jasper on 2/1/2024.
//

#ifndef NEBULA_MAIN_MESHCOMPONENT_HPP
#define NEBULA_MAIN_MESHCOMPONENT_HPP

#include "../api/ecs/Component.hpp"

#include "../graphics/mesh/Mesh.hpp"

namespace nebula {

    class MeshComponent : public Component{
        std::shared_ptr<Mesh> mesh;

    public:
        explicit MeshComponent(const std::shared_ptr<Mesh> &mesh);

        [[nodiscard]] const std::shared_ptr<Mesh> &getMesh() const;
    };

} // nebula

#endif //NEBULA_MAIN_MESHCOMPONENT_HPP
