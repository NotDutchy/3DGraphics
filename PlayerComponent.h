#pragma once
#include <GLFW/glfw3.h>

#include "Component.h"

class PlayerComponent : public Component
{
public:
	PlayerComponent(GLFWwindow* window);
	~PlayerComponent();

	void update(float elapsedTime) override;

private:
	void move(float angle, float speed);
	float speed = 0.5f;
	GLFWwindow* window;
};
