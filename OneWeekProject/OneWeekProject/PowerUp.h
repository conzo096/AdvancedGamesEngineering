#pragma once
#include "RenderableObject.h"
class PowerUp :
	public RenderableObject
{
public:

	enum PowerUpType
	{
		none, dualCannons, tripleCannons
	};
	PowerUp();
	~PowerUp();

	PowerUpType GetPowerUpType() 
	{
		return powerUp;
	}

	void SetPowerUpType(PowerUpType type)
	{
		powerUp = type;
	}

	float GetDuration()
	{
		return duration;
	}

	void SetDuration(float dur)
	{
		duration = dur;
	}
	void ReduceDuration(float dur)
	{
		duration -= dur;
	}

	void Draw(sf::RenderWindow &window);

	sf::IntRect spriteRect;

private:
	// Type of power up.
	PowerUpType powerUp;
	// How long it is to last for.
	float duration;
	sf::Clock clock;
};

