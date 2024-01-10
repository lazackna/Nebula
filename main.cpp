//
// Created by User on 12/24/2023.
//
#include "src/api/Nebula.hpp"

#include "entt/entt.hpp"
#include "src/api/ecs/Registry.hpp"

using namespace nebula;

struct e {
    int i = 0;

    explicit e(int i) : i(i) {}
};

int main() {
    NebulaOptions options(720, 480, "Nebula");
    Nebula engine = Nebula(options);

    class Test : public Component {

    };
    engine.start();
//    Registry reg;
//    auto o = reg.createGameObject();
//    o.lock()->addComponent<Test>();

    return 0;
}