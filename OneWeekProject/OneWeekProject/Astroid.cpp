#include "Astroid.h"
#include "PlayerShip.h"
#include "Game.h"

Astroid::Astroid()
{
	scoreValue = 100;
	fireRate = 0;
	cooldown = 0.0f;
	health = 200;
	LoadSprite("Images/GameObjects/DualCannons.png");
}


Astroid::~Astroid()
{
}

void Astroid::Update(float deltaTime)
{
	timeActive += deltaTime;
	PlayerShip* player = static_cast<PlayerShip*>
		(Game::Instance()->GetGameManager().Get("Player"));
	if (player != NULL)
	{
		sf::Vector2f playerPosition = player->GetPosition();
		//Move towards player.
		sf::Vector2f towardsDirection = playerPosition - GetPosition();
		//Calculate new angle to face player.
		float angle = std::atan2(towardsDirection.x, -towardsDirection.y) * (180 / 3.14);
		GetSprite().setRotation(angle);
		GetSprite().move((towardsDirection*2.0f)*deltaTime);

		// Check if they collide with player.
		if (player->GetSprite().getGlobalBounds().intersects(GetSprite().getGlobalBounds()))
			player->AddHealth(-200);
	}
	else
	{
		GetSprite().rotate(360 * deltaTime);
	}

}