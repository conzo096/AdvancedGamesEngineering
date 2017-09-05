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
	// What type of power up does the player has?
	PowerUp::PowerUpType power; 

};

