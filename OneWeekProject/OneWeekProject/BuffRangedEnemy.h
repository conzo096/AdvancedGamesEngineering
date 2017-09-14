#pragma once
#include "Ship.h"
class BuffRangedEnemy :
	public Ship
{
public:
	BuffRangedEnemy();
	~BuffRangedEnemy();
	void Update(float deltaTime);

};

