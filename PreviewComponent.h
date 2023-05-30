#pragma once
#include "Component.h"
#include "Camera.h"
class PreviewComponent : public Component
{
public:
	PreviewComponent(Camera* camera);
	~PreviewComponent();

	void update();
};

