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

void PreviewComponent::updatePreviewMatrix()
{
	glm::mat4 ret(1.0f);
	glm::vec3 position = gameObject->position;

	ret = glm::translate(ret, position);

	ret = glm::rotate(ret, gameObject->rotation.y, glm::vec3(0, 1, 0));

	ret = glm::rotate(ret, gameObject->rotation.x, glm::vec3(1, 0, 0));

	float zDistance = -.5f;

	position = glm::vec3(0.0f, 0.0f, zDistance);

	ret = glm::translate(ret, position);

	this->mat = ret;
}

void PreviewComponent::update(float elapsedTime)
{
	updatePreviewMatrix();
}