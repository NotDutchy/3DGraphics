#include "CameraComponent.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "GameObject.h"

CameraComponent::CameraComponent(GLFWwindow* window) : window(window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

CameraComponent::~CameraComponent()
{

}

glm::mat4 CameraComponent::getMatrix()
{
	glm::mat4 ret(1.0f);
	ret = glm::rotate(ret, gameObject->rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, gameObject->rotation.y, glm::vec3(0, 1, 0));
	ret = glm::translate(ret, gameObject->position);
	return ret;
}

void CameraComponent::update(float elapsedTime)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	static double lastX = x;
	static double lastY = y;

	float tempX = gameObject->rotation.x - (float)(lastY - y) / 100.f;

	if (tempX < 1.5f && tempX > -1.0f)
		gameObject->rotation.x = tempX;

	gameObject->rotation.y -= (float)(lastX - x) / 100.0f;

	lastX = x;
	lastY = y;
}
