#pragma once
#include "Ship.h"
class RangedEnemy : public Ship
{
public:
	RangedEnemy();
	~RangedEnemy();
	void Update(float deltaTime);
};

