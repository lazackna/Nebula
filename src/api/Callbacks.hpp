//
// Created by Jasper on 12/24/2023.
//

#ifndef NEBULA_MAIN_CALLBACKS_HPP
#define NEBULA_MAIN_CALLBACKS_HPP

#include <functional>
#include <string>

namespace nebula {
    using ErrorCallback = std::function<void(int errorCode, const std::string& description)>;
}
#endif //NEBULA_MAIN_CALLBACKS_HPP
