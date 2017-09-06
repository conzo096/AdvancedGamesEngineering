#pragma once
#include "RenderableObject.h"
#include "PowerUp.h"
#include "Bullet.h"
class PlayerShip : public RenderableObject
{
public:
	PlayerShip();
	~PlayerShip();
	void Update(float deltaTime);

	float GetHealth()
	{
		return health;
	}

	std::vector<Bullet*> bullets;
private:
	// What type of power up does the player has?
	PowerUp::PowerUpType power; 
	// Health of the player.
	float health;
	// Array of bullets the play has shot.
	
};

