#include "Astroid.h"
#include "PlayerShip.h"
#include "Game.h"

Astroid::Astroid()
{
}


Astroid::~Astroid()
{
}

void Astroid::Update(float deltaTime)
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
		float angle = std::atan2(towardsDirection.x, -towardsDirection.y) * (180 / 3.14);
		GetSprite().setRotation(angle);
		GetSprite().move(towardsDirection*deltaTime);
	}
	else
	{
		GetSprite().rotate(360 * deltaTime);
	}

}