#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "CameraComponent.h"
#include "GameManager.h"
#include "GameObject.h"
#include "ModelComponent.h"
#include "ObjModel.h"
#include "PathGenerator.h"
#include "TileComponent.h"
#include "MoveToComponent.h" 
#include "PlayerComponent.h"
#include "PreviewComponent.h"
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
PathGenerator* pathGenerator;
GameManager* gameManager;

int gridWidth = 10;
int gridHeight = 10;
double lastFrameTime = 0;

std::list<std::shared_ptr<GameObject>> objects;
std::list<std::shared_ptr<GameObject>> tiles;
std::shared_ptr<GameObject> turret;
std::shared_ptr<GameObject> player;
std::vector<Texture*> textures;
std::vector<ObjModel*> models;

std::vector<PathGenerator::Cell*> path;
std::vector<std::vector<int>> grid;

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
	gameManager->init();

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
		gameManager->despawnEnemies();
	}

	glfwTerminate();

	return 0;
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, true);
	tigl::shader->setLightPosition(0, glm::vec3(gridHeight / 2, 1,  gridWidth / 2));
	tigl::shader->setLightAmbient(0, glm::vec3(0.5f, 0.5f, 0.5f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.5f, 0.5f, 0.5f));
	tigl::shader->setLightSpecular(0, glm::vec3(1, 1, 1));
	tigl::shader->setShinyness(0);

	textures.push_back(new Texture("resource/textures/pathTexture2.jpg"));
	textures.push_back(new Texture("resource/textures/grass.jpg"));
	models.push_back(new ObjModel("models/turret/TurretLegacy.obj"));
	models.push_back(new ObjModel("models/enemy/RubberDuckLegacy.obj"));

	//Generate the grid for A*
	for (int i = 0; i < gridWidth; i++)
	{
		std::vector<int> columns;
		for (int j = 0; j < gridHeight; j++)
		{
			auto o = std::make_shared<GameObject>();
			o->position = glm::vec3(i, -1, j);
			tiles.push_back(o);
			columns.push_back(0);
		}
		grid.push_back(columns);
	}

	player = std::make_shared <GameObject>();
	player->position = glm::vec3(0, 0, 0);
	player->addComponent(std::make_shared<CameraComponent>(window));
	player->addComponent(std::make_shared<PlayerComponent>(window));

	pathGenerator = new PathGenerator(grid);
	path = pathGenerator->aStar(false);
	pathGenerator->printGrid();
	pathGenerator->printPath(path);
	pathGenerator->writePathToFile(path);

	gameManager = new GameManager(objects, tiles, path, models, player, window);

	for (auto& tile : tiles)
	{
		for (auto cell : path)
		{
			if ((tile->position.x == cell->row) && (tile->position.z == cell->col))
			{
				tile->addComponent(std::make_shared<TileComponent>(1.0f, textures[0], true));
			}
		}

		if (tile->getComponent<TileComponent>() != nullptr && tile->getComponent<TileComponent>()->isPath)
		{
			//std::cout << "Tile is part of path continuing\n";
		}
		else
		{
			//std::cout << "Adding regular tile to array\n";
			tile->addComponent(std::make_shared<TileComponent>(1.0f, textures[1], false)); //, 
		}
	}

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);
		});
}

void update()
{
	double currentFrameTime = glfwGetTime();
	double deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	for (auto& obj : objects)
	{
		obj->update((float) deltaTime);
	}

	gameManager->update();
	player->update(deltaTime);
}

void draw()
{
	glClearColor(0.3f, 0.5f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	auto cameraComponent = player->getComponent<CameraComponent>();

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(cameraComponent->getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));
	tigl::shader->enableColor(true);

	for (auto& tile : tiles)
	{
		tile->draw();
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		tile->draw();*/
	}

	/*for (PathGenerator::Cell* cell : path)
	{
		delete cell;
	}*/

	for (auto& o : objects)
	{
		o->draw();
	}

	if (player->getComponent<PreviewComponent>() != nullptr)
	{
		player->draw();
	}
}