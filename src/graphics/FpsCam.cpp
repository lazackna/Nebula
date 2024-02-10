#include "FpsCam.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

FpsCam::FpsCam(GLFWwindow* _window)
{
	window = _window;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    yaw = -90.0f;
    pitch = 0;

    updateVectors();
}


glm::mat4 FpsCam::getMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void FpsCam::update(float deltatime)
{
	double x, y;
	glfwGetCursorPos(window, &y, &x);

	static double lastX = x;
	static double lastY = y;

	float deltaY = (float)(lastX - x);
	float deltaX = (float)(lastY - y);

	lastX = x;
	lastY = y;

    float sensitivity = 0.5f;
    deltaX *= sensitivity;
    deltaY *= sensitivity;

    this->yaw -= deltaX;
    this->pitch += deltaY;

    if (this->pitch > 89.0f)
        this->pitch = 89.0f;
    if (this->pitch < -89.0f)
        this->pitch = -89.0f;

    float factor = 4;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += (1.0f + (10)) * deltatime * front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= (1.0f + (10)) * deltatime * front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * (1.0f + (10)) * deltatime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * (1.0f + (10)) * deltatime;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        position.y -= factor * deltatime;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        position.y += factor * deltatime;
    }

    updateVectors();
}

glm::vec3 FpsCam::getPosition()
{
	return position;
}

void FpsCam::setPosition(glm::vec3 _position)
{
	position = _position;
}

void FpsCam::updateVectors() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
}
