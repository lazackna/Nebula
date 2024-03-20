//
// Created by Jasper on 1/18/2024.
//
#pragma once
#ifndef NEBULA_MAIN_MATH_HPP
#define NEBULA_MAIN_MATH_HPP


#include "glm/glm.hpp"

void rotate(glm::mat4& mat, const glm::vec3& rotation) {
    mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1,0,0));
    mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0,1,0));
    mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0,0,1));
}

#endif //NEBULA_MAIN_MATH_HPP
