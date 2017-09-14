#pragma once
#include "RenderableObject.h"
#include "Bullet.h"
class Ship :
	public RenderableObject
{
public:
	Ship();
	~Ship();
	int GetHealth()
	{
		return health;
	}

	void SetHealth(int h)
	{
		health = h;
	}

	void AddHealth(int val)
	{
		health += val;
	}

	std::string GetName()
	{
		return name;
	}
	void SetName(std::string shipName)
	{
		name = shipName;
	}


protected:
	// Health of the ship.
	int health;
	// Ships name.
	std::string name;
	//Fire rate.
	float fireRate;
	//Time since last fire.
	float cooldown;
};

