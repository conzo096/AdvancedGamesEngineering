#pragma once
#include "Ship.h"
#include "PowerUp.h"
#include "Bullet.h"
class PlayerShip : public Ship
{
public:
	PlayerShip();
	~PlayerShip();
	void Update(float deltaTime);


private:
	// What type of power up does the player has?
	PowerUp *power; 

};

