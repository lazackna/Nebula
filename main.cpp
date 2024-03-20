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

void rotateMat(glm::mat4& mat, const glm::vec3& rotation) {
    mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1,0,0));
    mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0,1,0));
    mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0,0,1));
}

int main() {
    NebulaOptions options(1280, 720, "Nebula");
    Nebula engine = Nebula(options);

    std::shared_ptr<Renderer> deferredRenderer = std::make_shared<DeferredRenderer>(options.width, options.height,
                                                                                    engine.getWindow());

    engine.addRenderer(deferredRenderer);

    std::shared_ptr<Renderer> phongRenderer = std::make_shared<PhongRenderer>();
    engine.addRenderer(phongRenderer);


    Entity ground = Entity(loadMesh("resources/scenes/Test01/Resources/island.glb"));
    engine.addEntity(ground);

    Entity lightHouse = Entity(loadMesh("resources/scenes/Test01/Resources/kenney_piratekit_1.1/tower.glb"));
    auto lightHouseModel = lightHouse.model;
    lightHouseModel = glm::translate(lightHouseModel, glm::vec3(0, 1.3, 0));
    lightHouseModel = glm::scale(lightHouseModel, glm::vec3(0.5));
    lightHouse.model = lightHouseModel;
    engine.addEntity(lightHouse);

    Entity boat = Entity(loadMesh("resources/scenes/Test01/Resources/kenney_piratekit_1.1/boat_large.glb"));
    auto boatModel = boat.model;
    boatModel = glm::translate(boatModel, glm::vec3(-2, -0.075, 6));
    boatModel = glm::scale(boatModel, glm::vec3(0.5));
    boat.model = boatModel;
    engine.addEntity(boat);

//    Entity palmTree = Entity(loadMesh("resources/scenes/Test01/Resources/kenney_piratekit_1.1/palm_long.glb"));
//    auto palmTreeModel = palmTree.model;
//    palmTreeModel = glm::translate(palmTreeModel, glm::vec3(0,0,4));
//    palmTree.model = palmTreeModel;
//    engine.addEntity(palmTree);
//
    Entity captain = Entity(loadMesh("resources/scenes/Test01/Resources/kenney_piratekit_1.1/pirate_captain.glb"));
    auto captainModel = captain.model;
    captainModel = glm::translate(captainModel, glm::vec3(-2, -0.055, 6.3));
    captainModel = glm::scale(captainModel, glm::vec3(0.5));
    captain.model = captainModel;
    engine.addEntity(captain);

    Entity bottle = Entity(loadMesh("resources/scenes/Test01/Resources/kenney_piratekit_1.1/bottle.glb"));
    auto bottleModel = bottle.model;
    bottleModel = glm::translate(bottleModel, glm::vec3(2,1.4,0));
    bottleModel = glm::scale(bottleModel, glm::vec3(0.4));
    rotateMat(bottleModel, glm::vec3(0,0, -7));
    bottleModel = glm::translate(bottleModel, glm::vec3(0,-0.05,0));
    bottle.model = bottleModel;
    engine.addEntity(bottle);

    engine.start();
    return 0;
}