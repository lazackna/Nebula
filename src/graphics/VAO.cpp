//
// Created by User on 1/10/2024.
//

#include "VAO.hpp"

namespace nebula {

    void VAO::bind() const {
        glBindVertexArray(id);
    }

    void VAO::unbind(){
        glBindVertexArray(0);
    }

} // nebula