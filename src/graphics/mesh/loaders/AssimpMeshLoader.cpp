//
// Created by User on 1/22/2024.
//

#include "AssimpMeshLoader.hpp"

namespace nebula {
    Result<std::unique_ptr<Mesh>, std::runtime_error> AssimpMeshLoader::load(const std::filesystem::path &path) {
        return {std::runtime_error("nothing")};
    }
} // nebula