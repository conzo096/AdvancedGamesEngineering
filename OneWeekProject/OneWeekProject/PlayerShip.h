#pragma once
#include "RenderableObject.h"
#include "PowerUp.h"
class PlayerShip : public RenderableObject
{
public:
	PlayerShip();
	~PlayerShip();
	void Update(float deltaTime);
private:
	PowerUp::PowerUpType power; 

};

