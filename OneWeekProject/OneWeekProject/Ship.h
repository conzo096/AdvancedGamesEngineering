#pragma once
#include "RenderableObject.h"
#include "Bullet.h"
class Ship :
	public RenderableObject
{
public:
	Ship();
	~Ship();
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
	float health;
	// Ships name.
	std::string name;
	//Fire rate.
	float fireRate;
	//Time since last fire.
	float cooldown;
};

