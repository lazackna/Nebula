//
// Created by Jasper on 1/31/2024.
//

#ifndef NEBULA_MAIN_GLTBLOADER_HPP
#define NEBULA_MAIN_GLTBLOADER_HPP

#include "../MeshLoading.hpp"

namespace tinygltf {
    class Model;
    class Image;
}

namespace nebula {

    class GltbLoader : public MeshLoader {
        std::shared_ptr<Texture> imageToTexture(tinygltf::Image& image);
        void LoadTexture(tinygltf::Model& model, Material& material, int imageIndex, TextureType textureType, glm::vec4 fallbackColor);
    public:
        GltbLoader() = default;
        std::shared_ptr<Mesh> load(const std::filesystem::path &path) override;
    };

} // nebula

#endif //NEBULA_MAIN_GLTBLOADER_HPP
