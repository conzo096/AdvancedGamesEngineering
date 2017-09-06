#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
	std::map<std::string, RenderableObject*>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		DeleteObject(itr->first);
	}
}

void GameManager::AddObject(std::string name,RenderableObject* gameObject)
{
	gameObjects.insert(std::pair<std::string, RenderableObject*>(name, gameObject));
}

void GameManager::DeleteObject(std::string name)
{
	std::map<std::string, RenderableObject*>::iterator results = gameObjects.find(name);
	if (results != gameObjects.end())
	{
		delete results->second;
		gameObjects.erase(results);
	}
}


int GameManager::GetObjectCount() const
{
	return gameObjects.size();
}

RenderableObject* GameManager::Get(std::string name) const
{
	std::map<std::string, RenderableObject*>::const_iterator results = gameObjects.find(name);
	if (results == gameObjects.end())
		return NULL;
	return results->second;

}


void GameManager::UpdateAll(float deltaTime)
{
	std::map<std::string, RenderableObject*>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		itr->second->Update(deltaTime);
		itr++;
	}
}

void GameManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, RenderableObject*>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}