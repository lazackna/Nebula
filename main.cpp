//
// Created by User on 12/24/2023.
//
#include "src/api/Nebula.hpp"

#include "src/api/ecs/Registry.hpp"
#include "src/graphics/mesh/MeshLoading.hpp"
#include "src/Components/MeshComponent.hpp"

using namespace nebula;


int main() {
    NebulaOptions options(1280, 720, "Nebula");
    Nebula engine = Nebula(options);

    //auto& meshLoader = MeshLoading::getInstance();


    Registry reg;
    auto o = reg.createGameObject();
    //o.lock()->addComponent<MeshComponent>(meshLoader.load("resources/models/bottle/bottle.glb"));
    engine.start();
    return 0;
}