#include "TileComponent.h"


TileComponent::TileComponent(float size, Texture* texture)
{
	glm::vec3 s(size);
	glm::vec4 color(1,1,1,1);
	glm::vec3 p(0,0,0);
	this->texture = texture;

	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x / 2 , -s.y / 2, -s.z / 2), color, glm::vec2(0, 0), glm::vec3(0, -1, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x / 2, -s.y / 2, -s.z / 2), color, glm::vec2(1,0), glm::vec3(0,-1,0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x / 2, -s.y / 2, s.z / 2), color, glm::vec2(1,1), glm::vec3(0,-1,0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x / 2, -s.y / 2, s.z / 2), color, glm::vec2(0,1), glm::vec3(0,-1,0)));
}

TileComponent::~TileComponent()
{
	
}

void TileComponent::draw()
{
	if (texture)
	{
		texture->bind();
		tigl::shader->enableTexture(true);
		tigl::drawVertices(GL_QUADS, verts);
		tigl::shader->enableTexture(false);
		texture->unbind();
	}
}