#include "GameManager.h"
#include "RangedEnemy.h"
#include "Game.h"

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


// Spawn a new wave of enemies.
void GameManager::SpawnWave(sf::RenderWindow& renderWindow)
{
	int enemiesToSpawn = wave*3 +1;
	enemiesAlive = enemiesToSpawn;
	for (int i = 0; i < enemiesToSpawn; i++)
	{
		RangedEnemy* enemy = new RangedEnemy();
		enemy->LoadSprite("Images/GameObjects/EnemyShip1.png");
		enemy->SetHealth(75);
		// Need to add random feature to this (Spawn just out of view).
		enemy->SetPosition(50*i, 50);
		std::string enemyName = "Enemy"+ std::to_string(i);
		enemy->SetName(enemyName);
		AddObject(enemyName, enemy);
	}
	wave++;
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
	std::map<std::string, RenderableObject*>::iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		itr->second->Update(deltaTime);
		if (itr != gameObjects.end())
			itr++;
	}

	std::map<std::string, RenderableObject*>::iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		if(itr->second->toBeDeleted == true)
			gameObjects.erase(itr);
		else
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