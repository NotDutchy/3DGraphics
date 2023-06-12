#include "GameManager.h"
#include <iostream>
#include <thread>

#include "GameObject.h"
#include <GLFW/glfw3.h>
#include "ModelComponent.h"
#include "MoveToComponent.h"
#include "PreviewComponent.h"
#include "TileComponent.h"

int enemiesAlive = 0;

auto removeDead = [](std::shared_ptr<GameObject> object)
{
	if (object->isDead)
	{
		enemiesAlive--;
		return true;
	}
	return false;
};

GameManager::GameManager(std::list<std::shared_ptr<GameObject>>& objects,
	std::list<std::shared_ptr<GameObject>>& tiles,
	std::vector<PathGenerator::Cell*>& path,
	std::vector<ObjModel*>& models,
	std::shared_ptr<GameObject>& player,
	GLFWwindow* window
) : objects(objects), tiles(tiles), path(path), models(models), player(player), window(window)
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
	if (enemiesToSpawn == 0 && enemiesAlive == 0)
	{
		buildingPhase = true;
	}

	if (buildingPhase && glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !previewing)
	{
		player->addComponent(std::make_shared<PreviewComponent>(models[0]));
		previewing = true;
	}

	if (previewing && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		glm::vec3 newTurretPos = glm::vec3(0, 0, 0);
		for (const auto& tile : tiles)
		{
			const auto tileComponent = tile->getComponent<TileComponent>();
			glm::vec3 tilePos = tile->position;

			if (tileComponent->isPath)
			{
				std::cout << tileComponent->isPath << "\n";
				continue;
			}

			if (glm::distance(tilePos.x, -player->position.x + 1.0f) < glm::distance(newTurretPos.x, -player->position.x + 1.0f))
			{
				newTurretPos.x = tilePos.x;
				std::cout << "New turret x pos: " << newTurretPos.x << " Tile x Pos " << tilePos.x << "\n";
			}
			if (glm::distance(tilePos.z, -player->position.z) < glm::distance(newTurretPos.z, -player->position.z))
			{
				newTurretPos.z = tilePos.z;
				std::cout << "New turret z pos: " << newTurretPos.z << " Tile z Pos " << tilePos.z << "\n";

			}
		}
		std::cout << "Placing new turret at: " << newTurretPos.x << "," << newTurretPos.z << "\n";
		auto newTurret = std::make_shared<GameObject>();
		newTurret->position = newTurretPos;
		newTurret->addComponent(std::make_shared<ModelComponent>(models[0]));
		objects.push_back(newTurret);
		player->removeComponent<PreviewComponent>();
		previewing = false;
	}
}

void GameManager::init()
{
	std::thread spawnThread(&GameManager::spawnEnemies, this);
	spawnThread.detach();
}