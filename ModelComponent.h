#pragma once
#include "DrawComponent.h"
#include "ObjModel.h"
#include "tigl.h"

class ModelComponent : public DrawComponent
{
	ObjModel* model;
public:
	ModelComponent(std::string path);
	~ModelComponent();

	virtual void draw() override;
};

