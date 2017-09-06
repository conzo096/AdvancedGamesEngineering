#include "RangedEnemy.h"



RangedEnemy::RangedEnemy()
{
}


RangedEnemy::~RangedEnemy()
{
}

void RangedEnemy::Update(float deltaTime)
{
	timeActive += deltaTime;
	/*if ((int)timeActive % 5 == 0)
	{
		Bullet* bullet = new Bullet();
		bullet->LoadSprite("Images/GameObjects/Bullet.png");
		bullet->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width / 2), GetPosition().y - GetSprite().getGlobalBounds().height);
		bullet->GetVelocity() = sf::Vector2f(GetVelocity());
		bullets.push_back(bullet);
	}*/

}
