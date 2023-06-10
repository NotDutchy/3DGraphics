#include "PlayerComponent.h"
#include <GLFW/glfw3.h>
#include "GameObject.h"

PlayerComponent::PlayerComponent(GLFWwindow* window) : window(window)
{
	
}

PlayerComponent::~PlayerComponent()
{
	
}

void PlayerComponent::move(float angle, float speed)
{
	gameObject->position.x += (float)cos(gameObject->rotation.y + glm::radians(angle)) * speed;
	gameObject->position.z += (float)sin(gameObject->rotation.y + glm::radians(angle)) * speed;
}

void PlayerComponent::update(float elapsedTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		move(90, speed * elapsedTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		move(0, speed * elapsedTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		move(180, speed * elapsedTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		move(-90, speed * elapsedTime);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		gameObject->position.y -= speed * elapsedTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		gameObject->position.y += speed  * elapsedTime;
	}
}