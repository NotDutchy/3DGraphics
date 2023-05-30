#pragma once
#include "Component.h"
#include "Camera.h"
class PreviewComponent : public Component
{
public:
	PreviewComponent(Camera* camera, GLFWwindow* window);
	~PreviewComponent();

	Camera* camera;
	GLFWwindow* window;

	virtual void update(float elapsedTime) override;
	void move(float angle, float fac);
	void moveModel(float speed);
};

