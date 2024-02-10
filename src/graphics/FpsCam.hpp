#pragma once
#include <glm/glm.hpp>

struct GLFWwindow;

const float SPEED = 2.5f;

class FpsCam
{
	GLFWwindow* window;

    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 front = glm::vec3(0,0,-1);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 right = glm::vec3(1, 0, 0);
    glm::vec3 worldUp = glm::vec3(0, 1, 0);

    float yaw;
    float pitch;

    void updateVectors();

public:
	FpsCam(GLFWwindow*);

	glm::mat4 getMatrix();
    glm::vec3 getPosition();
    void update(float deltatime);
	void setPosition(glm::vec3 position);

};


