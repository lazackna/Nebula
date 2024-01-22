//
// Created by Jasper on 1/22/2024.
//

#ifndef NEBULA_MAIN_EBO_HPP
#define NEBULA_MAIN_EBO_HPP

#include <vector>
#include <memory>

namespace nebula {

    class EBO;
    using Ebo = std::unique_ptr<EBO>;

    class EBO {
        unsigned int id;
        size_t size;

    public:
        explicit EBO(const std::vector<unsigned int>& indices);

        size_t getSize() const;

        void bind() const;
        static void unbind();

        static Ebo create(const std::vector<unsigned int>& indices);
    };

} // nebula

#endif //NEBULA_MAIN_EBO_HPP
