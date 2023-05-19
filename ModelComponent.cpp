#include "ModelComponent.h"

ModelComponent::ModelComponent(std::string path)
{
	model = new ObjModel(path);
}

ModelComponent::~ModelComponent()
{
	
}

void ModelComponent::draw()
{
	model->draw();
}
