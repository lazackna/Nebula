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
    public:
        virtual ~MeshLoader() = default;

        virtual std::shared_ptr<Mesh> load(const std::filesystem::path& path) = 0;
    };

    class MeshLoading {
        std::map<std::string, std::unique_ptr<MeshLoader>> alternateLoaders;

        std::unique_ptr<MeshLoader> defaultLoader;

        static MeshLoading* instance;
    public:
        explicit MeshLoading(std::unique_ptr<MeshLoader> defaultLoader);

        static MeshLoading& getInstance();

        template<class T, typename... Args> requires std::is_base_of_v<MeshLoader, T>
        void registerMeshLoader(const std::string& signature, Args... args) {
            alternateLoaders[signature] = std::move(std::make_unique<T>(args...));
        }

        std::shared_ptr<Mesh> load(const std::filesystem::path& path);

    };
} // nebula

#endif //NEBULA_MAIN_MESHLOADING_HPP
