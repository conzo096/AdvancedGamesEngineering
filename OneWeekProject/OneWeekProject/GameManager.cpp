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

void GameManager::DeleteObjects(std::vector<std::string> names)
{
	for (auto &i : names)
	{
		std::map<std::string, RenderableObject*>::iterator results = gameObjects.find(i);
		if (results != gameObjects.end())
		{
			delete results->second;
			gameObjects.erase(results);
		}
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
		enemy->GetSprite().setOrigin(sf::Vector2f(float(enemy->GetSprite().getTexture()->getSize().x) / 2, float(enemy->GetSprite().getTexture()->getSize().y) / 2));
		// Need to add random feature to this (Spawn just out of view).
		enemy->SetPosition(i*(Game::Instance()->GetScreenWidth()/enemiesToSpawn), 50);
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
		itr++;
	}
	
	std::vector<Bullet*>::iterator it = bullets.begin();
	while (it != bullets.end())
	{
		(*it)->Update(deltaTime);
		it++;
	}


	std::vector<std::string> deletedList;
	for (auto it = gameObjects.cbegin(); it != gameObjects.cend();) 
	{
		if (it->second->toBeDeleted == true)
		{
			if(it->first != "Player")
				Game::Instance()->GetGameManager().enemiesAlive--;
			deletedList.push_back(it->first);
		}
		it++;
	}
	DeleteObjects(deletedList);
}

void GameManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, RenderableObject*>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}

	std::vector<Bullet*>::iterator it = bullets.begin();
	while (it != bullets.end())
	{
		(*it)->Draw(renderWindow);
		it++;
	}
}