#pragma once
#include "Bullet.h"
class PlayerBullet :
	public Bullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	void Update(float deltaTime);

};

