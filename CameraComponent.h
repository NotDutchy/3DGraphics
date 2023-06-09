#pragma once
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include "Component.h"

class CameraComponent : public Component
{
public:
	CameraComponent(GLFWwindow* window);
	~CameraComponent();

	glm::mat4 getMatrix();
	void update(float elapsedTime) override;
private:
	GLFWwindow* window;
};
