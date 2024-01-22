//
// Created by User on 1/22/2024.
//

#include "MeshLoading.hpp"

namespace nebula {

    MeshLoading* MeshLoading::instance;
    Result<std::unique_ptr<Mesh>, std::runtime_error> MeshLoading::load(const std::filesystem::path &path) {
        auto signature = path.extension().string();

        if(alternateLoaders.contains(signature)) {
            return alternateLoaders[signature]->load(path);
        } else {
            return defaultLoader->load(path);
        }
    }

    MeshLoading &MeshLoading::getInstance() {

        if(!instance) {
            throw std::runtime_error("Class Meshloading was not initialized");
        }

        return *instance;
    }

    MeshLoading::MeshLoading(std::unique_ptr<MeshLoader> defaultLoader) {
        if(instance) {
            throw std::runtime_error("Class Meshloading was already initialized");
        }

        this->defaultLoader = std::move(defaultLoader);
        instance = this;
    }

} // nebula