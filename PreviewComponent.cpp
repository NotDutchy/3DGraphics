#include "PreviewComponent.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "GameObject.h"
#include "ObjModel.h"

PreviewComponent::PreviewComponent(ObjModel* model) : model(model) {

}

PreviewComponent::~PreviewComponent()
{
	
}

void PreviewComponent::updatePreviewMatrix()
{
	if (model)
	{
		glm::mat4 ret(1.0f);
		glm::vec3 position = -gameObject->position;

		ret = glm::translate(ret, position);

		//ret = glm::rotate(ret, gameObject->rotation.y, glm::vec3(0, 1, 0));
		//ret = glm::rotate(ret, gameObject->rotation.x, glm::vec3(1, 0, 0));

		float zDistance = 1.0f;

		glm::vec3 pos = glm::vec3(zDistance, 0.0f, 0.0f);

		ret = glm::translate(ret, position);

		this->mat = ret;
	}
}

void PreviewComponent::update(float elapsedTime)
{
	updatePreviewMatrix();
}

void PreviewComponent::draw()
{
	if (model)
	{
		tigl::shader->setModelMatrix(this->mat);
		model->draw();
	}
}
