//
// Created by User on 12/24/2023.
//
#include "src/api/Nebula.hpp"

#include "src/api/ecs/Registry.hpp"
#include "src/graphics/mesh/MeshLoading.hpp"
#include "src/Components/MeshComponent.hpp"
#include "src/graphics/rendering/deferred/DeferredRenderer.hpp"
#include "src/graphics/rendering/phong/PhongRenderer.hpp"

using namespace nebula;


int main() {
    NebulaOptions options(1280, 720, "Nebula");
    Nebula engine = Nebula(options);

    //std::shared_ptr<Renderer> renderer = std::make_shared<DeferredRenderer>(options.width, options.height);
    std::shared_ptr<Renderer> renderer = std::make_shared<PhongRenderer>();
    engine.setRenderer(renderer);


    Entity ground = Entity(loadMesh("resources/scenes/Test01/Resources/island.glb"));
    engine.addEntity(ground);


    engine.start();
    return 0;
}