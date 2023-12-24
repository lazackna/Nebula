//
// Created by User on 12/24/2023.
//
#include "src/api/Nebula.hpp"

using namespace nebula;

int main() {
    NebulaOptions options(720, 480, "Nebula");
    Nebula engine = Nebula(options);

    engine.start();
    return 0;
}