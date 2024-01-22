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

}


glm::mat4 FpsCam::getMatrix()
{
	glm::mat4 ret(1.0f);
	ret = glm::rotate(ret, rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, rotation.y, glm::vec3(0, 1, 0));
	ret = glm::translate(ret, position);
	return ret;
}

void FpsCam::move(float angle, float fac, float deltatime)
{
	position.x += ((float)cos(rotation.y + glm::radians(angle)) * fac) * deltatime;
	position.z += ((float)sin(rotation.y + glm::radians(angle)) * fac) * deltatime;
}



void FpsCam::update(float deltatime)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	static double lastX = x;
	static double lastY = y;

	float deltaY = (float)(lastX - x);
	float deltaX = (float)(lastY - y);

	rotation.x -= (float)(lastY - y) / 300.0f;
	rotation.y -= (float)(lastX - x) / 300.0f;

	lastX = x;
	lastY = y;

    float factor = 0.05f * 100;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(0, factor, deltatime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(180, factor, deltatime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move(90, factor, deltatime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move(-90, factor, deltatime);
}

glm::vec3 FpsCam::getPosition()
{
	return position;
}

void FpsCam::setPosition(glm::vec3 _position)
{
	position = _position;
}
