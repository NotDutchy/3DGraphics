#pragma once
#include <memory>
#include "GameObject.h"
#include "ObjModel.h"
#include "PathGenerator.h"
#include "GLFW/glfw3.h"

class GameManager
{
public:
	GameManager(std::list<std::shared_ptr<GameObject>>& objects, std::list<std::shared_ptr<GameObject>>& tiles, std::vector<PathGenerator::Cell*>& path, std::vector<ObjModel*>& models, std::shared_ptr<GameObject>& player, GLFWwindow* window);
	~GameManager();

	std::list<std::shared_ptr<GameObject>>& objects;
	std::list<std::shared_ptr<GameObject>>& tiles;
	std::vector<PathGenerator::Cell*>& path;
	std::vector<ObjModel*>& models;
	std::shared_ptr<GameObject>& player;
	GLFWwindow* window;

	bool isOver = false;
	bool buildingPhase = false;
	bool previewing = false;
	int enemiesToSpawn = 5;

	void spawnEnemies();
	void despawnEnemies();
	void update();
	void init();
};

