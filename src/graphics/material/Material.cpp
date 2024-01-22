//
// Created by Jasper on 1/22/2024.
//

#include "Material.hpp"

#include "../../shaders/Shader.hpp"

namespace nebula {
    void Material::use(Shader &shader) const {
        shader.setMaterial(*this);
    }

    void Material::addTexture(TextureType type, const std::shared_ptr<Texture>& texture) {
        textureMap.insert(std::pair<TextureType, std::shared_ptr<Texture>>(type, texture));
    }
} // nebula