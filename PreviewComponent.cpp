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
		gameObject->position.x += speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		gameObject->position.z -= speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		gameObject->position.z += speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		gameObject->position.x -= speed;
	}
}

void PreviewComponent::update(float elapsedTime)
{
	moveModel(0.5f);
}