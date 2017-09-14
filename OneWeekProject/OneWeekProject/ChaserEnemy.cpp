#include "ChaserEnemy.h"
#include "PlayerShip.h"
#include "Game.h"
#include <math.h>
ChaserEnemy::ChaserEnemy()
{
	scoreValue = 20;
	cooldown = 0.0f;
	health = 25;
	LoadSprite("Images/GameObjects/EnemyShip2.png");
	GetSprite().setOrigin(sf::Vector2f(float(GetSprite().getTexture()->getSize().x) / 2, float(GetSprite().getTexture()->getSize().y) / 2));
}


ChaserEnemy::~ChaserEnemy()
{
}

void ChaserEnemy::Update(float deltaTime)
{
	timeActive += deltaTime;
	cooldown -= deltaTime;
	PlayerShip* player = static_cast<PlayerShip*>
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
		float angle = std::atan2(towardsDirection.x, -towardsDirection.y) * (180 / 3.14);
		GetSprite().setRotation(angle);
		float mag = std::sqrt(std::pow(towardsDirection.x, 2) + std::pow(towardsDirection.y, 2));
		towardsDirection.x /= mag;
		towardsDirection.y /= mag;
		towardsDirection*= 600.0f;

		if (GetSprite().getGlobalBounds().intersects(player->GetSprite().getGlobalBounds()) && !player->toBeDeleted && !toBeDeleted)
		{
			// This bullet is to be deleted.
			toBeDeleted = true;
			player->AddHealth(-health);
			health = 0;
			return;
		}
		GetSprite().move(towardsDirection*deltaTime);

	}
	else
	{
		GetSprite().rotate(360 * deltaTime);
	}

}
