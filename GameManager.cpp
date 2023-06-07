#include "GameManager.h"
#include <iostream>
#include <thread>

#include "GameObject.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include "ModelComponent.h"
#include "MoveToComponent.h"
#include "PreviewComponent.h"

auto removeDead = [](std::shared_ptr<GameObject> object)
{
	if (object->isDead)
	{
		std::cout << "Deleting object\n";
		return true;
	}
	return false;
};

GameManager::GameManager(std::list<std::shared_ptr<GameObject>>& objects,
                         std::vector<PathGenerator::Cell*>& path,
                         std::vector<ObjModel*>& models,
                         GLFWwindow* window,
                         Camera* camera
)	: objects(objects), path(path), models(models), window(window), camera(camera)
{

}

GameManager::~GameManager()
{
}

void GameManager::spawnEnemies()
{
	while (!isOver && !buildingPhase)
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

void GameManager::despawnEnemies()
{
	
	objects.remove_if(removeDead);
}

void GameManager::update()
{
	if (buildingPhase && glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		auto preview = std::make_shared<GameObject>();
		//preview->position = glm::vec3(camera->position.x + 1, camera->position.y, camera->position.z);
		preview->position = glm::vec3(0, 0 ,0);
		//preview->rotation = glm::vec3(camera->rotation.x, camera->rotation.y, 0);
		preview->addComponent(std::make_shared<ModelComponent>(models[0]));
		preview->addComponent(std::make_shared<PreviewComponent>(camera, window));
		objects.push_back(preview);
	}
}

void GameManager::init()
{
	std::thread spawnThread(&GameManager::spawnEnemies, this);
	spawnThread.detach();
}
