//
// Created by User on 1/22/2024.
//

#ifndef NEBULA_MAIN_ASSIMPMODELLOADER_HPP
#define NEBULA_MAIN_ASSIMPMODELLOADER_HPP

#include "../MeshLoading.hpp"
#include "../Mesh.hpp"
#include <assimp/scene.h>

namespace nebula {

    class Texture;

    class AssimpMeshLoader : public MeshLoader {
    private:
        void processNode(Mesh& mesh, aiNode* node, const aiScene* scene);
        static std::unique_ptr<Mesh::Primitive> processPrimitive(Mesh& mesh, aiMesh* primitive, const aiScene* scene);
        static std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string typeName);
    public:
        Result<std::unique_ptr<Mesh>, std::runtime_error> load(const std::filesystem::path &path) override;
    };

} // nebula

#endif //NEBULA_MAIN_ASSIMPMODELLOADER_HPP
