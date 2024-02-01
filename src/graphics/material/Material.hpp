//
// Created by Jasper on 1/22/2024.
//

#ifndef NEBULA_MAIN_MATERIAL_HPP
#define NEBULA_MAIN_MATERIAL_HPP

#include <memory>
#include <map>
#include "Texture.hpp"
#include "TextureType.hpp"

namespace nebula {

    class Shader;

    class Material {
        std::map<TextureType, std::shared_ptr<Texture>> textureMap;

    public:
        Material() = default;

        void use(Shader& shader) const;
        void addTexture(TextureType type, const std::shared_ptr<Texture>& texture);

        const std::map<TextureType, std::shared_ptr<Texture>> &getTextureMap() const;
    };

} // nebula

#endif //NEBULA_MAIN_MATERIAL_HPP
