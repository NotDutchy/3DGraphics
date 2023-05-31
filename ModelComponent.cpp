#include "ModelComponent.h"

ModelComponent::ModelComponent(ObjModel* model) : model(model)
{
	
}

ModelComponent::~ModelComponent()
{
	
}

void ModelComponent::draw()
{
	model->draw();
}