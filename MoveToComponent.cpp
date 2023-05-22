#include "MoveToComponent.h"

#include "GameObject.h"

MoveToComponent::MoveToComponent(std::vector<PathGenerator::Cell*> &path) : path(path)
{
	target = glm::vec3(this->path[nextTarget]->row, 0, this->path[nextTarget]->col);
}

MoveToComponent::~MoveToComponent()
{
	
}

void MoveToComponent::update(float elapsedTime)
{ 
	if ((gameObject->position.x >= target.x - 0.01f) && (gameObject->position.z >= target.z - 0.01f) && nextTarget < path.size())
	{
		std::cout << "Setting next target\n";
		target = glm::vec3(path[nextTarget]->row, 0, path[nextTarget]->col);
		nextTarget++;
	}

	gameObject->position = (1 - speed) * gameObject->position + speed * target;

	float angle = atan2(gameObject->position.z - target.z, gameObject->position.x - target.x);
	gameObject->rotation.y = 0.05f * angle + 0.95f * gameObject->rotation.y;
}