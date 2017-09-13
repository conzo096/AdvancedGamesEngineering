#pragma once
#include "stdafx.h"
#include "RenderableObject.h"
#include "Bullet.h"
#include "SFMLSoundProvider.h"
#include "ServiceLocator.h"
class GameManager
{
public:

	struct GreaterScore
	{
		template<class T>
		bool operator()(T const &a, T const &b) const { return a > b; }
	}; 
	GameManager();
	~GameManager();

	void UpdateAll(float deltaTime);
	void DrawAll(sf::RenderWindow& renderWindow);
	void StopSounds();
	int GameManager::GetObjectCount() const;
	RenderableObject* GameManager::Get(std::string name) const;
	void AddObject(std::string name,RenderableObject* gameObject);
	void DeleteObject(std::string name);
	void DeleteObjects(std::vector<std::string> names);
	void DeleteAll();
	std::map<std::string, RenderableObject*>& GetGameObjects()
	{
		return gameObjects;
	}

	std::list<Bullet*>& GetBullets()
	{
		return bullets;
	}
	// Players score.
	int score;
	// Wave player is on.
	int wave;
	// condition to spawn to new wave.
	bool createNewWave = true;
	// How many enemies are alive.
	int enemiesAlive;
	void SpawnWave(sf::RenderWindow& renderWindow);

	void PlaySong(std::string filePath, bool loop = true);
	void PlayClip(std::string filePath);
private:
	// Entity manager.
	std::map<std::string, RenderableObject*> gameObjects;
	// List of all the bullets in the scene.
	std::list<Bullet*> bullets;
	// Audio Manager.
	SFMLSoundProvider soundProvider;
	
	float spawnNewAstroid = 15;


	struct GameObjectDeallocator
	{
		void operator() (const std::pair<std::string, RenderableObject*>& p) const
		{
			delete p.second;
		}
	};

	
};

