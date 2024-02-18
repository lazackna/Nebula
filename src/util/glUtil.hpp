//
// Created by Jasper on 1/19/2024.
//
#pragma once
#ifndef NEBULA_MAIN_GLUTIL_HPP
#define NEBULA_MAIN_GLUTIL_HPP
#include <glm/glm.hpp>


glm::mat4 createPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);

glm::mat4 createOrthographic(float left, float right, float bottom, float top);

void enableWireframe(bool enable);

void drawCube();

void checkGLError(const char* file, int line);

#endif //NEBULA_MAIN_GLUTIL_HPP
