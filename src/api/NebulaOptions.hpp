//
// Created by Jasper on 12/24/2023.
//

#ifndef NEBULA_MAIN_NEBULAOPTIONS_HPP
#define NEBULA_MAIN_NEBULAOPTIONS_HPP

#include <string>
#include <utility>

#include <optional>
#include <functional>

#include "Callbacks.hpp"

namespace nebula {
    struct NebulaOptions {
        int width;
        int height;
        std::string name;

        std::optional<ErrorCallback> errorCallback;

        NebulaOptions(int width, int height, std::string name,
                      const std::optional<ErrorCallback> &errorCallback = std::nullopt) : width(
                width), height(height), name(std::move(name)), errorCallback(errorCallback) {}
    };
}
#endif //NEBULA_MAIN_NEBULAOPTIONS_HPP
