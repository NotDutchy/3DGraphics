#pragma once
#include "Component.h"
#include "DrawComponent.h"
#include "ObjModel.h"

class PreviewComponent : public DrawComponent
{
public:
	PreviewComponent(ObjModel* model);
	~PreviewComponent();

	virtual void update(float elapsedTime) override;
	void updatePreviewMatrix();
	void draw() override;

private:
	glm::mat4 mat;
	ObjModel* model;
};

