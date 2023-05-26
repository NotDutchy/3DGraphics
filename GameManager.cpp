#include "GameManager.h"
#include <iostream>
#include <thread>

#include "GameObject.h"
#include "ModelComponent.h"
#include "MoveToComponent.h"

GameManager::GameManager(std::list<std::shared_ptr<GameObject>>& objects, 
						 std::vector<PathGenerator::Cell*>& path,
                         std::vector<ObjModel*>& models
) : objects(objects), path(path), models(models)
{
}

GameManager::~GameManager()
{
}

void GameManager::spawnEnemies()
{
	while (!isOver && !endOfRound)
	{
		std::cout << "Spawning Enemy\n";
		auto enemy = std::make_shared<GameObject>();
		enemy->position = glm::vec3(0, 0, 0);
		enemy->addComponent(std::make_shared<ModelComponent>(models[1]));
		enemy->addComponent(std::make_shared<MoveToComponent>(path));
		objects.push_back(enemy);
		std::this_thread::sleep_for(std::chrono::seconds(5)); 
	}
}

void GameManager::update()
{
}

void GameManager::init()
{
	std::thread spawnThread(&GameManager::spawnEnemies, this);
	spawnThread.detach();
}
