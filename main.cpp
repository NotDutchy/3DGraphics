#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

int width = 1400, height = 800;
void init();
void update();
void draw();

int main(void)
{
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);

	tigl::init();

	init();

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


	return 0;
}

void init()
{
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);
		});

	glEnable(GL_DEPTH_TEST);
}

void drawCube(const glm::vec3& size)
{
	tigl::begin(GL_QUADS);

	//Achterkant Z
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, -size.y / 2, -size.z / 2), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, -size.y / 2, -size.z / 2), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, size.y / 2, -size.z / 2), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, size.y / 2, -size.z / 2), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)));

	//Voorkant Z
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, -size.y / 2, size.z / 2), glm::vec4(0.0f, 1.0f, 0.8f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, -size.y / 2, size.z / 2), glm::vec4(0.0f, 1.0f, 0.8f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, size.y / 2, size.z / 2), glm::vec4(0.0f, 1.0f, 0.8f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, size.y / 2, size.z / 2), glm::vec4(0.0f, 1.0f, 0.8f, 1.0f)));

	//Onderkant Y
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, -size.y / 2, -size.z / 2), glm::vec4(1.0f, 0.5f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, -size.y / 2, -size.z / 2), glm::vec4(1.0f, 0.5f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, -size.y / 2, size.z / 2), glm::vec4(1.0f, 0.5f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, -size.y / 2, size.z / 2), glm::vec4(1.0f, 0.5f, 1.0f, 1.0f)));

	//Bovenkant Y
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, size.y / 2, -size.z / 2), glm::vec4(1.0f, 0.1f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, size.y / 2, -size.z / 2), glm::vec4(1.0f, 0.1f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, size.y / 2, size.z / 2), glm::vec4(1.0f, 0.1f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, size.y / 2, size.z / 2), glm::vec4(1.0f, 0.1f, 1.0f, 1.0f)));

	//Achterkant X
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, -size.y / 2, -size.z / 2), glm::vec4(0.5f, 1.0f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, size.y / 2, -size.z / 2), glm::vec4(0.5f, 1.0f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, size.y / 2, size.z / 2), glm::vec4(0.5f, 1.0f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, -size.y / 2, size.z / 2), glm::vec4(0.5f, 1.0f, 1.0f, 1.0f)));

	//Voorkant X
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, -size.y / 2, -size.z / 2), glm::vec4(0.1f, 1.0f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, size.y / 2, -size.z / 2), glm::vec4(0.1f, 1.0f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, size.y / 2, size.z / 2), glm::vec4(0.1f, 1.0f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, -size.y / 2, size.z / 2), glm::vec4(0.1f, 1.0f, 1.0f, 1.0f)));

	tigl::end();
}

void update()
{

}

glm::vec3 ballPosition(0, 0, 0);

void draw()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(80.0f), (float)width / height, 0.1f, 100.0f));
	tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(0, 7, -12), ballPosition, glm::vec3(0, 1, 0)));
	tigl::shader->enableColor(true);

	//zijkanten
	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(8.5f, 0, 0)));
	drawCube(glm::vec3(1, 5, 1));

	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-8.5, 0, 0)));
	drawCube(glm::vec3(1, 5, 1));

	//voor/achter
	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 8.5f)));
	drawCube(glm::vec3(1, 5, 1));

	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -8.5)));
	drawCube(glm::vec3(1, 5, 1));

	//tigl::shader->enableColorMult(true);
	//tigl::shader->setColorMult(glm::vec4(1, 1, 1, 1));
	//tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5f, 0)));
	//drawCube(glm::vec3(16, 1, 16));
}
