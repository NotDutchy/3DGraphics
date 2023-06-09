#pragma once
#include <vector>

#include "DrawComponent.h"
#include "Texture.h"
#include "tigl.h"
using tigl::Vertex;

class TileComponent : public DrawComponent
{
	std::vector<tigl::Vertex> verts;
	Texture* texture;

public:
	TileComponent(float size, Texture* texture, bool isPath); //, 
	~TileComponent();

	bool isPath = false;

	virtual void draw() override;
};

