#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}


void Camera::move()
{
	//int state = glfwGetKey(display->getWindow(), GLFW_KEY_E);
	//if (state == GLFW_PRESS);
	
	if (glfwGetKey(display->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		this->position.z -= .02f;
	}
	if (glfwGetKey(display->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		this->position.x -= .02f;
	}
	if (glfwGetKey(display->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		this->position.z += .02f;
	}
	if (glfwGetKey(display->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		this->position.x += .02f;
	}
}