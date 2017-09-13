#include "Astroid.h"
#include "PlayerShip.h"
#include "Game.h"

Astroid::Astroid()
{
	scoreValue = 5;
	fireRate = 0;
	cooldown = 0.0f;
	health = 200;
	LoadSprite("Images/GameObjects/Astroid.png");
	const PlayerShip* player = static_cast<PlayerShip*>
		(Game::GetGameManager().Get("Player"));
	if (player != NULL)
	{
		sf::Vector2f playerPosition = player->GetPosition();
		//Move towards player.
		sf::Vector2f towardsDirection = playerPosition - GetPosition();
		//Calculate new angle to face player.
		float angle = std::atan2(towardsDirection.x, -towardsDirection.y) * (180 / 3.14);
		GetSprite().setRotation(angle);
		velocity = towardsDirection*0.8f ;
	}

}


Astroid::~Astroid()
{
}

void Astroid::Update(float deltaTime)
{
	timeActive += deltaTime;

	GetSprite().move(velocity*deltaTime);
	if (health <= 0)
		toBeDeleted = true;
	if(timeActive > 4)
		toBeDeleted = true;
}