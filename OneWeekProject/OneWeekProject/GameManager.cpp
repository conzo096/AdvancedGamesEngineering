#include "GameManager.h"
#include "RangedEnemy.h"
#include "ChaserEnemy.h"
#include "Astroid.h"
#include "Game.h"
#include "PowerUp.h"
#include "BuffRangedEnemy.h"
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
	// Min number to spawn.
	int enemiesToSpawn = wave*3 +1;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(-1500,1500);
	std::uniform_int_distribution<int> dist(0,10);

	for (int i = 0; i < enemiesToSpawn; i++)
	{
		// Decide what enemy to spawn. 10% for astroid.
		int bias = dist(generator);
		if (bias < 2 && wave >2)
		{
			Astroid* astroid = new Astroid();
			bool valid = false;
			sf::Vector2f spawnLoc = sf::Vector2f(0, 0);
			while (!valid)
			{
				float x = distribution(generator);
				float y = distribution(generator);
				spawnLoc = sf::Vector2f(x, y);
				sf::FloatRect bounds(sf::Vector2f(0.f, 0.f), sf::Vector2f(Game::GetRenderWindow().getView().getSize().x, Game::GetRenderWindow().getView().getSize().y));

				// Check if it is off screen
				if (!bounds.contains(spawnLoc))
				{
					valid = true;
				}
			}
			i--;
			astroid->SetPosition(spawnLoc.x,spawnLoc.y);
			std::string enemyName = "Astroid" + std::to_string(i);
			AddObject(enemyName, astroid);
		}
		else if (bias > 2 && bias < 5)
		{
			ChaserEnemy* enemy = new ChaserEnemy();
			// Need to add random feature to this (Spawn just out of view).
			bool valid = false;
			sf::Vector2f spawnLoc = sf::Vector2f(0, 0);
			while (!valid)
			{
				float x = distribution(generator);
				float y = distribution(generator);
				spawnLoc = sf::Vector2f(x, y);
				sf::FloatRect bounds(sf::Vector2f(0.f, 0.f), sf::Vector2f(Game::GetRenderWindow().getView().getSize().x, Game::GetRenderWindow().getView().getSize().y));

				// Check if it is off screen
				if (!bounds.contains(spawnLoc))
				{
					valid = true;
				}

			}
			//enemy->SetPosition(i*(Game::Instance()->GetScreenWidth() / enemiesToSpawn), 50);
			enemy->SetPosition(spawnLoc.x, spawnLoc.y);
			std::string enemyName = "Enemy" + std::to_string(i);
			enemy->SetName(enemyName);
			AddObject(enemyName, enemy);
			enemiesAlive++;
		}
		
		else
		{
			if (wave >3 && bias >=7)
			{
				BuffRangedEnemy* enemy = new BuffRangedEnemy();
				// Need to add random feature to this (Spawn just out of view).
				bool valid = false;
				sf::Vector2f spawnLoc = sf::Vector2f(0, 0);
				while (!valid)
				{
					float x = distribution(generator);
					float y = distribution(generator);
					spawnLoc = sf::Vector2f(x, y);
					sf::FloatRect bounds(sf::Vector2f(0.f, 0.f), sf::Vector2f(Game::GetRenderWindow().getView().getSize().x, Game::GetRenderWindow().getView().getSize().y));

					// Check if it is off screen
					if (!bounds.contains(spawnLoc))
					{
						valid = true;
					}

				}
				//enemy->SetPosition(i*(Game::Instance()->GetScreenWidth() / enemiesToSpawn), 50);
				enemy->SetPosition(spawnLoc.x, spawnLoc.y);
				std::string enemyName = "Enemy B" + std::to_string(i);
				enemy->SetName(enemyName);
				AddObject(enemyName, enemy);
				enemiesAlive++;
			}

			RangedEnemy* enemy = new RangedEnemy();
			// Need to add random feature to this (Spawn just out of view).
			bool valid = false;
			sf::Vector2f spawnLoc = sf::Vector2f(0, 0);
			while (!valid)
			{
				int x = distribution(generator);
				int y = distribution(generator);
				spawnLoc = sf::Vector2f(x, y);
				sf::FloatRect bounds(sf::Vector2f(0.f, 0.f), sf::Vector2f(Game::GetRenderWindow().getView().getSize().x, Game::GetRenderWindow().getView().getSize().y));

				// Check if it is off screen
				if (!bounds.contains(spawnLoc))
				{
					valid = true;
				}

			}
			//enemy->SetPosition(i*(Game::Instance()->GetScreenWidth() / enemiesToSpawn), 50);
			enemy->SetPosition(spawnLoc.x, spawnLoc.y);
			std::string enemyName = "Enemy" + std::to_string(i);
			enemy->SetName(enemyName);
			AddObject(enemyName, enemy);
			enemiesAlive++;
		}
	}
	wave++;

	// Spawn randomly.

	PowerUp* power = new PowerUp();
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

void GameManager::StopSounds()
{
	soundProvider.StopAllSounds();
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
	spawnNewAstroid -= deltaTime;
	if (spawnNewAstroid <= 0)
	{
		Astroid* astroid = new Astroid();
		bool valid = false;
		sf::Vector2f spawnLoc = sf::Vector2f(0, 0);
		while (!valid)
		{
			float x = rand() % 3000 - 1500;
			float y = rand() % 4000 - 2000;
			spawnLoc = sf::Vector2f(x, y);
			sf::FloatRect bounds(sf::Vector2f(0.f, 0.f), sf::Vector2f(Game::GetRenderWindow().getView().getSize().x, Game::GetRenderWindow().getView().getSize().y));

			// Check if it is off screen
			if (!bounds.contains(spawnLoc))
			{
				valid = true;
			}
		}
		astroid->SetPosition(spawnLoc.x, spawnLoc.y);
		std::string enemyName = "Astroid" + std::to_string(spawnLoc.x);
		AddObject(enemyName, astroid);
		// Spawn a new astroid between 1 and 19 seconds;
		spawnNewAstroid = rand() % 19 + 1;
	}

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
			if (strstr(it->first.c_str(), "Enemy") || strstr(it->first.c_str(), "Astroid"))
			{
				if (strstr(it->first.c_str(), "Enemy"))
				{
					Game::Instance()->GetGameManager().enemiesAlive--;
					Game::Instance()->GetGameManager().score += it->second->scoreValue;
				}
			}
			deletedList.push_back(it->first);
		}
		it++;
	}	
	// Handle collisions with objects still active.
	for (auto obj = GetGameObjects().begin(); obj != GetGameObjects().end(); ++obj)
	{
		for (auto obj1 = std::next(obj); obj1 != GetGameObjects().end(); ++obj1)
		{
			// If an astroid collides with an object.
			if (strstr(obj->first.c_str(), "Astroid"))
			{
				if(obj->second->GetSprite().getGlobalBounds().intersects(obj1->second->GetSprite().getGlobalBounds()))
				{
					// Destroy the second object.
					Ship* ship = static_cast<Ship*>(obj1->second);
					if (ship != NULL)
					{
						ship->SetHealth(0);
						ship->toBeDeleted = true;
					}
				}
			}
			if (strstr(obj1->first.c_str(), "Astroid"))
			{
				if (obj->second->GetSprite().getGlobalBounds().intersects(obj1->second->GetSprite().getGlobalBounds()))
				{
						Ship* ship = static_cast<Ship*>(obj->second);
					if (ship != NULL)
					{
						ship->SetHealth(0);
						ship->toBeDeleted = true;
					}
				}
			}

			// If two enemies collide.
			else if (strstr(obj->first.c_str(), "Enemy") || strstr(obj1->first.c_str(), "Enemy"))
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
	DeleteObjects(deletedList);
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