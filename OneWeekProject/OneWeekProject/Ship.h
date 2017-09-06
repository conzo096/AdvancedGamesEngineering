#pragma once
#include "RenderableObject.h"
#include "Bullet.h"
class Ship :
	public RenderableObject
{
public:
	Ship();
	~Ship();
	void Draw(sf::RenderWindow& renderWindow);
	float GetHealth()
	{
		return health;
	}

	void SetHealth(float h)
	{
		health = h;
	}

	void AddHealth(float val)
	{
		health = val;
	}

	//Returns the vector of bullets.
	std::vector<Bullet*>& GetBullets()
	{
		return bullets;
	}
protected:
	float health;
	// Array of bullets the play has shot.
	std::vector<Bullet*> bullets;
};

