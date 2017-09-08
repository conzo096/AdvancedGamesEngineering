#include "RangedEnemy.h"
#include "PlayerShip.h"
#include "Game.h"
#include <math.h>
#include "EnemyBullet.h"
RangedEnemy::RangedEnemy()
{
	scoreValue = 50;
	fireRate = 1.5f;
	cooldown = 0.0f;
}


RangedEnemy::~RangedEnemy()
{
}

void RangedEnemy::Update(float deltaTime)
{
	timeActive += deltaTime;

	const PlayerShip* player = static_cast<PlayerShip*>
		(Game::Instance()->GetGameManager().Get("Player"));
	if (player != NULL)
	{
		sf::Vector2f playerPosition = player->GetPosition();
		//Move towards player.
		sf::Vector2f towardsDirection = playerPosition - GetPosition();
		//Calculate new angle to face player.
		float angle =  std::atan2(towardsDirection.x, -towardsDirection.y) * (180/3.14);

		GetSprite().setRotation(angle);
		GetSprite().move(towardsDirection*deltaTime);

		if ((int)timeActive % 8 == 1)
		{
			if (cooldown <= 0)
			{
				EnemyBullet* bullet = new EnemyBullet();
				bullet->LoadSprite("Images/GameObjects/Bullet.png");
				bullet->belongsTo = GetName();
				bullet->SetPosition(GetSprite().getPosition().x, GetSprite().getPosition().y);
				// Normalise then times by Speed *Create bullet property*
				bullet->GetVelocity() = sf::Vector2f(towardsDirection);
				Game::Instance()->GetGameManager().GetBullets().push_back(bullet);
				cooldown = fireRate;
			}
		}
	}
	else
	{
		GetSprite().rotate(360 * deltaTime);
	}

}
