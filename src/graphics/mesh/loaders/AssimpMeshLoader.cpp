//
// Created by User on 1/22/2024.
//

#include "AssimpMeshLoader.hpp"
#include "../../material/Texture.hpp"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

namespace nebula {

    std::shared_ptr<Mesh> AssimpMeshLoader::load(const std::filesystem::path &path) {

        auto mesh = std::make_shared<Mesh>();

        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path.string().c_str(),
                                                 aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                                                 aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            return mesh;
        }

        processNode(*mesh, scene->mRootNode, scene);

        return mesh;
    }

    void AssimpMeshLoader::processNode(Mesh& mesh, aiNode *node, const aiScene *scene) { // NOLINT(*-no-recursion)
        for(int i = 0; i < node->mNumMeshes; ++i) {
            aiMesh* primitive = scene->mMeshes[node->mMeshes[i]];

            //load mesh here
            mesh.addPrimitive(processPrimitive(primitive, scene));
        }

        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(mesh, node->mChildren[i], scene);
        }
    }

    std::unique_ptr<Mesh::Primitive> AssimpMeshLoader::processPrimitive(aiMesh *primitive, const aiScene *scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        for(unsigned int i = 0; i < primitive->mNumVertices; ++i) {
            glm::vec3 position {primitive->mVertices[i].x, primitive->mVertices[i].y, primitive->mVertices[i].z};
            glm::vec3 normals {0,1, 0};
            glm::vec2 texCoords {0,0};
            if(primitive->HasNormals()) {
                normals = {primitive->mNormals[i].x, primitive->mNormals[i].y, primitive->mNormals[i].z};
            }
            if(primitive->mTextureCoords[0]) {
                texCoords = {primitive->mTextureCoords[0][i].x, primitive->mTextureCoords[0][i].y};
            }
            vertices.push_back(Vertex::PTN(position, texCoords, normals));
        }

        for(unsigned int i = 0; i < primitive->mNumFaces; i++)
        {
            aiFace face = primitive->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        Material material;
        aiMaterial* aiMat = scene->mMaterials[primitive->mMaterialIndex];

        processMaterial(aiMat, material);

        return std::make_unique<Mesh::Primitive>(vertices, indices, material, " ");
    }

    void AssimpMeshLoader::processMaterial(aiMaterial *aiMat, Material &material) {
        processTextures(aiMat, material);
    }

    void AssimpMeshLoader::processTextures(aiMaterial *aiMat, Material &material) {
        for (unsigned int i = 0; i < aiMat->GetTextureCount(aiTextureType_DIFFUSE); ++i) {
            aiString path;
            if (aiMat->GetTexture(aiTextureType_DIFFUSE, i, &path) == AI_SUCCESS) {
                std::shared_ptr<Texture> texture = std::make_shared<Texture>(path.C_Str());
                material.addTexture(TextureType::ALBEDO, texture);
            }
        }
    }
//
//    std::vector<std::shared_ptr<Texture>>
//    AssimpMeshLoader::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string typeName) {
//        std::vector<std::shared_ptr<Texture>> textures;
//
//        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
//            aiString str;
//            mat->GetTexture(type, i, &str);
//            bool skip = false;
//
//            //Check if we already loaded the texture
////            for (unsigned int j = 0; j < textures_loaded.size(); j++) {
////                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
////                }
////
////            }
//
//            if(!skip) {
//                textures.emplace_back(std::make_shared<Texture>(str.C_Str()));
//            }
//        }
//
//        return textures;
//    }
} // nebula