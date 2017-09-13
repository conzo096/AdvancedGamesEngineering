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
	health = 75;
	LoadSprite("Images/GameObjects/EnemyShip1.png");
	GetSprite().setOrigin(sf::Vector2f(float(GetSprite().getTexture()->getSize().x) / 2, float(GetSprite().getTexture()->getSize().y) / 2));
	cooldown = (rand() % 3) + 1;
}


RangedEnemy::~RangedEnemy()
{
}

void RangedEnemy::Update(float deltaTime)
{
	timeActive += deltaTime;
	cooldown-=deltaTime;
	const PlayerShip* player = static_cast<PlayerShip*>
		(Game::GetGameManager().Get("Player"));
	if (player != NULL)
	{
		sf::Vector2f playerPosition = player->GetPosition();
		//Move towards player.
		sf::Vector2f towardsDirection = playerPosition - GetPosition();
		//Check that the enemy is staying a fixed distance away.
		float distance = std::sqrt(
			std::pow(towardsDirection.x, 2) +
			std::pow(towardsDirection.y, 2));
		//Calculate new angle to face player.
		float angle =  std::atan2(towardsDirection.x, -towardsDirection.y) * (180/3.14);

		if (cooldown <= 0)
		{
			EnemyBullet* bullet = new EnemyBullet();
			bullet->LoadSprite("Images/GameObjects/Bullet.png");
			bullet->belongsTo = GetName();
			bullet->SetPosition(GetSprite().getPosition().x, GetSprite().getPosition().y);
			// Normalise then times by Speed *Create bullet property*
			float mag = std::sqrt(std::pow(towardsDirection.x, 2) + std::pow(towardsDirection.y, 2));
			towardsDirection.x/ mag;
			towardsDirection.y / mag;
			bullet->GetVelocity() = sf::Vector2f(towardsDirection);
			Game::GetGameManager().GetBullets().push_back(bullet);
			//cooldown = fireRate;
			cooldown = (rand() % 2) + 0.25;
		}

		GetSprite().setRotation(angle);
		if(distance > 150)
			GetSprite().move(towardsDirection*deltaTime);
		if (distance == 150)
			GetSprite().move(sf::Vector2f(0, 0));
		if(distance < 150)
		{
			// Chose a new direction.
			//towardsDirection.x += rand() % 50 - 50;
			//towardsDirection.y += rand() % 50 - 50;
			GetSprite().move(-towardsDirection*0.5f*deltaTime);
		}
	}
	else
	{
		GetSprite().rotate(360 * deltaTime);
	}

}
