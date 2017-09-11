#include "GameManager.h"
#include "RangedEnemy.h"
#include "Game.h"
#include "PowerUp.h"
#include <random>
#include <iterator>
GameManager::GameManager()
{
	ServiceLocator::RegisterServiceLocator(&soundProvider);
}


GameManager::~GameManager()
{
	std::map<std::string, RenderableObject*>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		DeleteObject(itr->first);
	}

	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet* bullet)
	{
		return bullet->toBeDeleted;
	}), bullets.end());


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
		DeleteObject(i);
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

		// Need to add random feature to this (Spawn just out of view).
		enemy->SetPosition(i*(Game::Instance()->GetScreenWidth()/enemiesToSpawn), 50);
		std::string enemyName = "Enemy"+ std::to_string(i);
		enemy->SetName(enemyName);
		AddObject(enemyName, enemy);
	}
	wave++;

	PowerUp* power = new PowerUp();
	power->LoadSprite("Images/GameObjects/DualCannons.png");
	power->SetPosition(200, 200);
	PowerUp::PowerUpType type = static_cast<PowerUp::PowerUpType>(rand() % 3);
	power->SetPowerUpType(type);
	power->SetDuration(5);
	AddObject("PowerUpD", power);
}

void GameManager::PlaySong(std::string filePath,bool loop)
{
	soundProvider.PlaySong(filePath,loop);
}

void GameManager::PlayClip(std::string filePath)
{
	soundProvider.PlaySound(filePath);
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
	// Update bullets.
	std::list<Bullet*>::iterator it = bullets.begin();
	while (it != bullets.end())
	{
		(*it)->Update(deltaTime);
		it++;
	}
	// Update other game objects.
	std::map<std::string, RenderableObject*>::iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		if(!itr->second->toBeDeleted)
			itr->second->Update(deltaTime);
		itr++;
	}


	// Delete bullets that have expired.
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet* bullet)
	{
		return bullet->toBeDeleted;
		if (bullet->toBeDeleted)
			delete bullet;
	}), bullets.end());
	
	// Delete game objects that have expired.
	std::vector<std::string> deletedList;
	for (auto it = gameObjects.cbegin(); it != gameObjects.cend();) 
	{
		if (it->second->toBeDeleted == true)
		{
			if (strstr(it->first.c_str(), "Enemy"))
			{
				Game::Instance()->GetGameManager().enemiesAlive--;
				Game::Instance()->GetGameManager().score += it->second->scoreValue;
			}
			deletedList.push_back(it->first);
		}
		it++;
	}
	DeleteObjects(deletedList);
	
	// Handle collisions with objects still active.
	for (auto obj = GetGameObjects().begin(); obj != GetGameObjects().end(); ++obj)
	{
		for (auto obj1 = std::next(obj); obj1 != GetGameObjects().end(); ++obj1)
		{
			if (strstr(obj->first.c_str(), "Enemy") || strstr(obj1->first.c_str(), "Enemy"))
			{
				while (obj->second->GetSprite().getGlobalBounds().intersects(obj1->second->GetSprite().getGlobalBounds()))
				{
					sf::Vector2f towardsDirection = obj->second->GetSprite().getPosition() - obj1->second->GetSprite().getPosition();
					// Resolve the first one only.
					obj1->second->GetSprite().move(-towardsDirection*deltaTime);
					obj->second->GetSprite().move(towardsDirection*deltaTime);
				}
			}
		}

	}
}


void GameManager::DeleteAll()
{
	// Delete bullets and game objects.
	std::vector<std::string> names;
	for (auto pair : gameObjects)
	{
		names.push_back(pair.first);
	}
	DeleteObjects(names);
	for (auto bullet : bullets)
	{
		delete bullet;
	}
	// Resize containers.
	gameObjects.clear();
	bullets.clear();

	
}



void GameManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, RenderableObject*>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}

	std::list<Bullet*>::iterator it = bullets.begin();
	while (it != bullets.end())
	{
		(*it)->Draw(renderWindow);
		it++;
	}
}