#include "ModelComponent.h"

ModelComponent::ModelComponent(std::string path)
{
	model = new ObjModel(path);
	//model = new ObjModel("models/turret/TowerDefenseTurret.obj");
}

ModelComponent::~ModelComponent()
{
	
}

void ModelComponent::draw()
{
	model->draw();
}
