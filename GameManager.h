#pragma once
#include <memory>
#include "GameObject.h"
#include "ObjModel.h"
#include "PathGenerator.h"

class GameManager
{
public:
	GameManager(std::list<std::shared_ptr<GameObject>>& objects, std::vector<PathGenerator::Cell*>& path, std::vector<ObjModel*> &models);
	~GameManager();

	std::list<std::shared_ptr<GameObject>>& objects;
	std::vector<PathGenerator::Cell*>& path;
	std::vector<ObjModel*>& models;


	bool isOver = false;
	bool endOfRound = false;

	void spawnEnemies();
	void update();
	void init();
};

