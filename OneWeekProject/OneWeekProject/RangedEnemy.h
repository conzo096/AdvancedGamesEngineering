#pragma once
#include "Ship.h"
class RangedEnemy : public Ship
{
public:
	RangedEnemy();
	~RangedEnemy();
	void Update(float deltaTime);
	void SetFireRate(float f)
	{
		fireRate = f;
	}
	void SetHealth(float h)
	{
		health = h;
	}

};

