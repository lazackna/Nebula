//
// Created by User on 1/22/2024.
//

#ifndef NEBULA_MAIN_MESHLOADING_HPP
#define NEBULA_MAIN_MESHLOADING_HPP

#include <filesystem>
#include <memory>
#include <map>

#include "../../util/Result.hpp"
#include "Mesh.hpp"

namespace nebula {
    class MeshLoader {
    protected:
        const std::vector<std::string> extensions;

        explicit MeshLoader(const std::vector<std::string>& extensions) : extensions(extensions){}
    public:
        virtual ~MeshLoader() = default;

        virtual std::shared_ptr<Mesh> load(const std::filesystem::path& path) = 0;

        bool canLoad(const std::string& extension);
    };

    void registerMeshLoader(std::unique_ptr<MeshLoader>);

    std::shared_ptr<Mesh> loadMesh(const std::filesystem::path& path);
} // nebula

#endif //NEBULA_MAIN_MESHLOADING_HPP
