//
// Created by User on 1/22/2024.
//

#ifndef NEBULA_MAIN_ASSIMPMESHLOADER_HPP
#define NEBULA_MAIN_ASSIMPMESHLOADER_HPP

#include "../MeshLoading.hpp"

namespace nebula {

    class AssimpMeshLoader : public MeshLoader {
    public:
        Result<std::unique_ptr<Mesh>, std::runtime_error> load(const std::filesystem::path &path) override;
    };

} // nebula

#endif //NEBULA_MAIN_ASSIMPMESHLOADER_HPP
