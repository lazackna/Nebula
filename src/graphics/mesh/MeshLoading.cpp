//
// Created by User on 1/22/2024.
//

#include "MeshLoading.hpp"

#include <algorithm>

namespace nebula {

    std::vector<std::unique_ptr<MeshLoader>> meshLoaders;

    void registerMeshLoader(std::unique_ptr<MeshLoader> loader) {
        meshLoaders.push_back(std::move(loader));
    }

    std::shared_ptr<Mesh> loadMesh(const std::filesystem::path &path) {
        auto extension = path.extension().string();

        for (const auto &item: meshLoaders) {
            if(item->canLoad(extension)) {
                return item->load(path);
            }
        }

        return nullptr;
    }

    bool MeshLoader::canLoad(const std::string &extension) {
        return std::find(extensions.begin(), extensions.end(), extension) != extensions.end();
    }
} // nebula