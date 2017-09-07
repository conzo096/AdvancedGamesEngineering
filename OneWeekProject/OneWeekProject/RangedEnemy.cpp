#include "RangedEnemy.h"
#include "PlayerShip.h"
#include "Game.h"
#include <math.h>

RangedEnemy::RangedEnemy()
{
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
			Bullet* bullet = new Bullet();
			bullet->LoadSprite("Images/GameObjects/Bullet.png");
			bullet->belongsTo = GetName();
			bullet->SetPosition(GetSprite().getPosition().x, GetSprite().getPosition().y);
			//bullet->SetPosition( GetPosition().x + (GetSprite().getGlobalBounds().width / 2), GetPosition().y - GetSprite().getGlobalBounds().height);
			// Normalise then times by Speed *Create bullet property*
			bullet->GetVelocity() = sf::Vector2f(towardsDirection);
			Game::Instance()->GetGameManager().GetBullets().push_back(bullet);
		}

	}
	else
	{
		GetSprite().rotate(360 * deltaTime);
	}

}
