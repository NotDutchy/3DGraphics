#pragma once
#include <memory>
#include "GameObject.h"
#include "ObjModel.h"
#include "PathGenerator.h"
#include "GLFW/glfw3.h"
#include "Camera.h"

class GameManager
{
public:
	GameManager(std::list<std::shared_ptr<GameObject>>& objects, std::vector<PathGenerator::Cell*>& path, std::vector<ObjModel*> &models, GLFWwindow* window, Camera* camera);
	~GameManager();

	std::list<std::shared_ptr<GameObject>>& objects;
	std::vector<PathGenerator::Cell*>& path;
	std::vector<ObjModel*>& models;
	GLFWwindow* window;
	Camera* camera;

	bool isOver = false;
	bool endOfRound = false;

	void spawnEnemies();
	void update();
	void init();
};

