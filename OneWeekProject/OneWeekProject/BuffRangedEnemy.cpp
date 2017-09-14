#include "BuffRangedEnemy.h"
#include "RangedEnemy.h"
#include "Game.h"

BuffRangedEnemy::BuffRangedEnemy()
{
	LoadSprite("res/Images/GameObjects/BuffEnemy.png");
	scoreValue = 25;
	health = 80;
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
	RangedEnemy* followAlly = nullptr;
	while (itr != Game::GetGameManager().GetGameObjects().end())
	{
		if (strstr(itr->first.c_str(), "Enemy") && !strstr(itr->first.c_str(), "Enemy B") && itr->second != this)
		{
			RangedEnemy* ally = static_cast<RangedEnemy*>(itr->second);
			if(ally != nullptr)
			{ 
				// If this is the first enemy target it.
				if (followAlly == nullptr)
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
						followAlly->GetSprite().setColor(sf::Color::White);
						followAlly = ally;
					}
				}
			}
		}
		itr++;
	}

	// If it is following a target.
	if (followAlly != nullptr)
	{
		// Follow him.
		sf::Vector2f followPosition = followAlly->GetPosition();
		//Move towards player.
		sf::Vector2f towardsDirection = followPosition - GetPosition();
		// How far from the player.
		float distance = std::sqrt(
			std::pow(towardsDirection.x, 2) +
			std::pow(towardsDirection.y, 2));
		// Calculate normal for normal distance.
		float mag = std::sqrt(std::pow(towardsDirection.x, 2) + std::pow(towardsDirection.y, 2));
		towardsDirection.x /= mag;
		towardsDirection.y /= mag;
		towardsDirection *= 500.0f;
		//Calculate new angle to face player.
		float angle = std::atan2(towardsDirection.x, -towardsDirection.y) * (180 / 3.14);
		if (distance < 150)
		{
			followAlly->SetFireRate(3.0f);
			followAlly->ReduceCooldown(deltaTime*2);
			followAlly->GetVelocity()*1.5f;
			followAlly->GetSprite().setColor(sf::Color::Green);
		}

		GetSprite().rotate(angle*deltaTime);
		GetSprite().move(towardsDirection*deltaTime);
	}

	// If there is no ally to follow. Follow player?
	else
	{
		// Follow him.
		sf::Vector2f playerPosition = Game::GetGameManager().Get("Player")->GetPosition();
		//Move towards player.
		sf::Vector2f towardsDirection = playerPosition - GetPosition();
		//Calculate new angle to face player.
		float angle = std::atan2(towardsDirection.x, -towardsDirection.y) * (180 / 3.14);
		GetSprite().rotate(angle*deltaTime);
		GetSprite().move(towardsDirection*deltaTime);
	}

}
