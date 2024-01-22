//
// Created by User on 1/22/2024.
//

#ifndef NEBULA_MAIN_MESHLOADING_HPP
#define NEBULA_MAIN_MESHLOADING_HPP

#include <filesystem>
#include <memory>
#include <map>

#include "Mesh.hpp"
#include "../../util/Result.hpp"
namespace nebula {
    class MeshLoader {
    public:
        virtual ~MeshLoader() = default;

        virtual Result<std::unique_ptr<Mesh>, std::runtime_error> load(const std::filesystem::path& path) = 0;
    };

    class MeshLoading {
        std::map<std::string, std::unique_ptr<MeshLoader>> alternateLoaders;

        std::unique_ptr<MeshLoader> defaultLoader;

        MeshLoading* instance;
    public:
        template<class T, typename... Args>
        requires std::is_base_of_v<MeshLoader, T>
        explicit MeshLoading(Args... args) {
            if(instance) {
                throw std::runtime_error("Class Meshloading was already initialized");
            }

            this->defaultLoader = std::move(std::make_unique<T>(args...));
            instance = this;
        }

        MeshLoading& getInstance();

        template<class T, typename... Args> requires std::is_base_of_v<MeshLoader, T>
        void registerMeshLoader(const std::string& signature, Args... args) {
            alternateLoaders[signature] = std::move(std::make_unique<T>(args...));
        }

        Result<std::unique_ptr<Mesh>, std::runtime_error> load(const std::filesystem::path& path);

    };
} // nebula

#endif //NEBULA_MAIN_MESHLOADING_HPP
