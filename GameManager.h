#pragma once
#include <memory>
#include "GameObject.h"
#include "ObjModel.h"
#include "PathGenerator.h"
#include "GLFW/glfw3.h"

class GameManager
{
public:
	GameManager(std::list<std::shared_ptr<GameObject>>& objects, std::vector<PathGenerator::Cell*>& path, std::vector<ObjModel*> &models, GLFWwindow* window, std::shared_ptr<GameObject> player);
	~GameManager();

	std::list<std::shared_ptr<GameObject>>& objects;
	std::vector<PathGenerator::Cell*>& path;
	std::vector<ObjModel*>& models;
	std::shared_ptr<GameObject> player;
	GLFWwindow* window;

	bool isOver = false;
	bool buildingPhase = true;
	int enemiesToSpawn = 5;

	void spawnEnemies();
	void despawnEnemies();
	void update();
	void init();
};

