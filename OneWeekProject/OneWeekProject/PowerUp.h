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

private:
	enum powerUpType;
};

