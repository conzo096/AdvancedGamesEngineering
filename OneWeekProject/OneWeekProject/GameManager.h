#pragma once
#include "stdafx.h"
#include "RenderableObject.h"
class GameManager
{
public:
	GameManager();
	~GameManager();

	void UpdateAll(float deltaTime);
	void DrawAll(sf::RenderWindow& renderWindow);
	int GameManager::GetObjectCount() const;
	RenderableObject* GameManager::Get(std::string name) const;
	void AddObject(std::string name,RenderableObject* gameObject);
	void DeleteObject(std::string name);

	std::map<std::string, RenderableObject*>& GetGameObjects()
	{
		return gameObjects;
	}

private:
	// Wave player is on.
	int wave;
	// enemies to spawn.
	int enemiesToSpawn;
	// Entity manager.
	std::map<std::string, RenderableObject*> gameObjects;


	struct GameObjectDeallocator
	{
		void operator() (const std::pair<std::string, RenderableObject*>& p) const
		{
			delete p.second;
		}
	};
};

