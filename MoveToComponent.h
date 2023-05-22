#pragma once
#include <glm/vec3.hpp>

#include "Component.h"
#include "PathGenerator.h"

class MoveToComponent : public Component
{
public:
	float speed = 0.06f;
	int nextTarget = 1;
	glm::vec3 target;
	std::vector<PathGenerator::Cell*> path;

	MoveToComponent(std::vector<PathGenerator::Cell*> &path);
	~MoveToComponent();

	virtual void update(float elapsedTime) override;
	void updateTarget();
};

