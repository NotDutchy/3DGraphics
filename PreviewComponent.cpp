#include "PreviewComponent.h"

#include <GLFW/glfw3.h>

#include "GameObject.h"

PreviewComponent::PreviewComponent(Camera* camera, GLFWwindow* window) : camera(camera), window(window) {

}

PreviewComponent::~PreviewComponent()
{
	
}

/*void PreviewComponent::move(float angle, float fac)
{
	gameObject->position.x += (float)cos(gameObject->rotation.y + glm::radians(angle)) * fac;
	gameObject->position.z += (float)sin(gameObject->rotation.y + glm::radians(angle)) * fac;
}*/

void PreviewComponent::moveModel(float speed)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//move(90, speed);
		gameObject->position.x += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		gameObject->position.z -= 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		gameObject->position.z += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		gameObject->position.x -= 0.1f;
	}
}

void PreviewComponent::update(float elapsedTime)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	static double lastX = x;
	static double lastY = y;

	float tempX = gameObject->rotation.x - (float)(lastY - y) / 100.f;

	gameObject->rotation.y -= (float)(lastX - x) / 100.0f;

	lastX = x;
	lastY = y;

	moveModel(0.1f);
}