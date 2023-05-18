#pragma once
#include <vector>

#include "DrawComponent.h"
#include "tigl.h"
using tigl::Vertex;

class TileComponent : public DrawComponent
{
	std::vector<tigl::Vertex> verts;
public:
	TileComponent(float size);
	~TileComponent();

	virtual void draw() override;
};

