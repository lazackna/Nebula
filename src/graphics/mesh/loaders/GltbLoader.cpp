//
// Created by Jasper on 1/31/2024.
//

#include "GltbLoader.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT

#include "nlohmann/json.hpp"
#include "tiny_gltf.h"
#include <cstring>
#include <iostream>

namespace nebula {
    std::shared_ptr<Mesh> GltbLoader::load(const std::filesystem::path &path) {

        auto mesh = std::make_shared<Mesh>();

        tinygltf::Model model;
        tinygltf::TinyGLTF loader;
        std::string error;
        std::string warning;
        bool valid = false;

        if(path.extension().string() == ".glb") {
            valid = loader.LoadBinaryFromFile(&model, &error, &warning, path.string());
        } else {
            valid = loader.LoadASCIIFromFile(&model, &error, &warning, path.string());
        }

        if (!warning.empty()) {
            printf("Warn: %s\n", warning.c_str());
        }

        if (!error.empty()) {
            printf("Err: %s\n", error.c_str());
        }

        if (!valid) {
            printf("Failed to parse glTF\n");
            return std::shared_ptr<Mesh>();
        }

        //our mesh is a primitive
        for(size_t m = 0; m < model.meshes.size(); m++) {
            std::cout << "loading " << model.meshes[m].name << std::endl;
            std::string name;
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
            Material material;

            for (const tinygltf::Primitive &primitive: model.meshes[m].primitives) {
                if(!model.materials.empty()) {
                    auto primitiveMaterial = model.materials[primitive.material];
                    auto pbrMaterial = primitiveMaterial.pbrMetallicRoughness;

                    glm::vec4 baseColor;
                    baseColor.r = pbrMaterial.baseColorFactor[0];
                    baseColor.g = pbrMaterial.baseColorFactor[1];
                    baseColor.b = pbrMaterial.baseColorFactor[2];
                    baseColor.a = pbrMaterial.baseColorFactor[3];
                    LoadTexture(model, material, pbrMaterial.baseColorTexture.index, TextureType::ALBEDO, baseColor);

                    baseColor.r = pbrMaterial.metallicFactor;
                    baseColor.g = pbrMaterial.roughnessFactor;
                    baseColor.b = 0;
                    baseColor.a = 0;
                    LoadTexture(model, material, pbrMaterial.metallicRoughnessTexture.index, TextureType::METALLICROUGHNESS, baseColor);

                    int normalIndex = primitiveMaterial.normalTexture.index;
                    if (normalIndex >= 0 && normalIndex < model.textures.size()) {
                        int normalImageIndex = model.textures[normalIndex].source;
                        if (normalImageIndex >= 0 && normalImageIndex < model.images.size()) {
                            auto normalTexture = imageToTexture(model.images[normalImageIndex]);
                            normalTexture->name = model.images[normalImageIndex].name;
                            material.addTexture(TextureType::NORMAL, std::make_shared<Texture>(*normalTexture));
                        }
                    }
                }

                //indices
                const tinygltf::Accessor &accessor = model.accessors[primitive.indices];
                const tinygltf::BufferView &bufferView = model.bufferViews[accessor.bufferView];

                const tinygltf::Buffer &buffer = model.buffers[bufferView.buffer];
                const uint16_t *indicesArr = reinterpret_cast<const uint16_t *>(&buffer.data[bufferView.byteOffset +
                                                                                             accessor.byteOffset]);
                for (size_t i = 0; i < accessor.count; i++) {
                    indices.push_back(indicesArr[i]);
                }

                //position
                const tinygltf::Accessor &posAccessor = model.accessors[primitive.attributes.at("POSITION")];
                const tinygltf::BufferView &posBufferView = model.bufferViews[posAccessor.bufferView];
                const tinygltf::Buffer &posBuffer = model.buffers[posBufferView.buffer];
                const float *positions = reinterpret_cast<const float *>(&posBuffer.data[posBufferView.byteOffset +
                                                                                         posAccessor.byteOffset]);

                //normal
                const tinygltf::Accessor &normalAccessor = model.accessors[primitive.attributes.at("NORMAL")];
                const tinygltf::BufferView &normalBufferView = model.bufferViews[normalAccessor.bufferView];
                const tinygltf::Buffer &normalBuffer = model.buffers[normalBufferView.buffer];
                const float *normalsFloats = reinterpret_cast<const float *>(&normalBuffer.data[
                        normalBufferView.byteOffset + normalAccessor.byteOffset]);

                //uv
                const tinygltf::Accessor &uvAccessor = model.accessors[primitive.attributes.at("TEXCOORD_0")];
                const tinygltf::BufferView &uvBufferView = model.bufferViews[uvAccessor.bufferView];
                const tinygltf::Buffer &uvBuffer = model.buffers[uvBufferView.buffer];
                const float *uvs = reinterpret_cast<const float *>(&uvBuffer.data[uvBufferView.byteOffset + uvAccessor.byteOffset]);

                for (int i = 0; i < posAccessor.count; ++i) {
                    vertices.push_back(Vertex::PTN(glm::vec3(positions[i * 3 + 0], positions[i * 3 + 1], positions[i * 3 + 2]),
                                              glm::vec2(uvs[i * 2 + 0], uvs[i * 2 + 1]),
                                                   glm::vec3(normalsFloats[i * 3 + 0], normalsFloats[i * 3 + 1],
                                                             normalsFloats[i * 3 + 2])));

                }
            }
            mesh->addPrimitive(std::make_unique<Mesh::Primitive>(vertices, indices, material, model.meshes[m].name));
        }

        return mesh;
    }

    void GltbLoader::LoadTexture(tinygltf::Model &model, Material &material, int imageIndex, TextureType textureType,
                                 glm::vec4 fallbackColor) {
        int baseColorIndex = imageIndex;
        if (baseColorIndex >= 0 && baseColorIndex < model.textures.size()) {
            int imageIndex = model.textures[baseColorIndex].source;
            if (imageIndex >= 0 && imageIndex < model.images.size()) {

                auto texture = imageToTexture(model.images[imageIndex]);
                texture->name = model.images[imageIndex].name;
                material.addTexture(textureType, texture);

            }
        } else {
            glm::vec4 baseColor;
            baseColor.r = fallbackColor[0];
            baseColor.g = fallbackColor[1];
            baseColor.b = fallbackColor[2];
            baseColor.a = fallbackColor[3];
            auto texture = std::make_shared<Texture>(baseColor);
            texture->name = "GeneratedAmbientTexture";
            material.addTexture(textureType, texture);
        }
    }

    std::shared_ptr<Texture> GltbLoader::imageToTexture(tinygltf::Image &image) {
        GLenum format = GL_RGBA;

        if (image.component == 1) {
            format = GL_RED;
        } else if (image.component == 2) {
            format = GL_RG;
        } else if (image.component == 3) {
            format = GL_RGB;
        } else {
            // ???
        }

        GLenum type = GL_UNSIGNED_BYTE;
        if (image.bits == 8) {
            // ok
        } else if (image.bits == 16) {
            type = GL_UNSIGNED_SHORT;
        } else {
            // ???
        }

        return std::make_shared<Texture>(image.image, image.width, image.height, format, type);
    }
} // nebula