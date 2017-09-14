#include "BuffRangedEnemy.h"
#include "RangedEnemy.h"
#include "Game.h"

BuffRangedEnemy::BuffRangedEnemy()
{
}


BuffRangedEnemy::~BuffRangedEnemy()
{
}

void BuffRangedEnemy::Update(float deltaTime)
{
	timeActive += deltaTime;
	cooldown -= deltaTime;

	// Iterate through each item in the map.
	std::map<std::string, RenderableObject*>::iterator itr = Game::GetGameManager().GetGameObjects().begin();
	RangedEnemy* followAlly;
	while (itr != Game::GetGameManager().GetGameObjects().end())
	{
		if (strstr(itr->first.c_str(), "Enemy"))
		{

			RangedEnemy* ally = static_cast<RangedEnemy*>(itr->second);
			// If this is the first enemy target it.
			if (followAlly = NULL)
				followAlly = ally;
			sf::Vector2f allyPosition = ally->GetPosition();
			//Move towards player.
			sf::Vector2f towardsDirection = allyPosition - GetPosition();
			//Check that the enemy is staying a fixed distance away.
			float distance = std::sqrt(
				std::pow(towardsDirection.x, 2) +
				std::pow(towardsDirection.y, 2));
			 
			if (followAlly != NULL)
			{
				sf::Vector2f tDirection = followAlly->GetPosition() - GetPosition();
				// Check who is closer.
				float dist = std::sqrt(
					std::pow(tDirection.x, 2) +
					std::pow(tDirection.y, 2));
				if (distance < dist)
				{
					followAlly = ally;
				}
			}
		}
	}

	if (followAlly != NULL)
	{
		// Follow him.
		sf::Vector2f playerPosition = followAlly->GetPosition();
		//Move towards player.
		sf::Vector2f towardsDirection = playerPosition - GetPosition();
		//Check that the enemy is staying a fixed distance away.
		float distance = std::sqrt(
			std::pow(towardsDirection.x, 2) +
			std::pow(towardsDirection.y, 2));
		//Calculate new angle to face player.
		float angle = std::atan2(towardsDirection.x, -towardsDirection.y) * (180 / 3.14);
		if (distance < 150)
		{
			followAlly->SetFireRate(0.1f);
		}
		GetSprite().move(towardsDirection*deltaTime);
	}
}
