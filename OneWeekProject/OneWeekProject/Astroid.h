#pragma once
#include "Ship.h"
class Astroid :public Ship
{
public:
	Astroid();
	~Astroid();

	void Update(float deltaTime);
};

