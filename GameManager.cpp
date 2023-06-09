#include "GameManager.h"
#include <iostream>
#include <thread>

#include "GameObject.h"
#include <GLFW/glfw3.h>
#include "ModelComponent.h"
#include "MoveToComponent.h"
#include "PreviewComponent.h"

int enemiesAlive = 0;

auto removeDead = [](std::shared_ptr<GameObject> object)
{
	if (object->isDead)
	{
		enemiesAlive--;
		std::cout << "Enemies Alive: " << enemiesAlive << "\n";
		return true;
	}
	return false;
};

GameManager::GameManager(std::list<std::shared_ptr<GameObject>>& objects,
                         std::vector<PathGenerator::Cell*>& path,
                         std::vector<ObjModel*>& models,
                         GLFWwindow* window,
						 std::shared_ptr<GameObject> player
)	: objects(objects), path(path), models(models), window(window), player(player)
{

}

GameManager::~GameManager()
{
}

void GameManager::spawnEnemies()
{
	
	while (!isOver && !buildingPhase && enemiesToSpawn > 0)
	{
		std::cout << "Spawning Enemy\n";
		auto enemy = std::make_shared<GameObject>();
		enemy->position = glm::vec3(0, 0, 0);
		enemy->addComponent(std::make_shared<ModelComponent>(models[1]));
		enemy->addComponent(std::make_shared<MoveToComponent>(path));
		objects.push_back(enemy);
		enemiesToSpawn--;
		enemiesAlive++;
		std::this_thread::sleep_for(std::chrono::seconds(5)); 
	}
}

void GameManager::despawnEnemies()
{
	objects.remove_if(removeDead);
}

void GameManager::update()
{
	if (buildingPhase && glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		player->addComponent(std::make_shared<PreviewComponent>(models[0]));
	}

	if (enemiesToSpawn == 0 && enemiesAlive == 0)
	{
		buildingPhase = true;
	}
}

void GameManager::init()
{
	std::thread spawnThread(&GameManager::spawnEnemies, this);
	spawnThread.detach();
}
