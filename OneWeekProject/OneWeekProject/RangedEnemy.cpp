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
		float angle =  std::atan2(towardsDirection.x, -towardsDirection.y) * (180/3.14);

		if ((int)timeActive % 8 == 1)
		{
			Bullet* bullet = new Bullet();
			bullet->LoadSprite("Images/GameObjects/Bullet.png");
			bullet->belongsTo = GetName();
			bullet->SetPosition( GetPosition().x + (GetSprite().getGlobalBounds().width / 2), GetPosition().y - GetSprite().getGlobalBounds().height);
			bullet->GetVelocity() = sf::Vector2f(towardsDirection);
			Game::Instance()->GetGameManager().GetBullets().push_back(bullet);

			//bullets.push_back(bullet);
		}

		//// Update all the bullets.
		//std::vector<Bullet*>::iterator itr = GetBullets().begin();
		//while (itr != GetBullets().end())
		//{
		//	if ((*itr)->toBeDeleted == false)
		//		(*itr)->Update(deltaTime);
		//	else
		//	{
		//		GetBullets().erase(itr);
		//		break;
		//	}
		//	itr++;
		//}


		GetSprite().setRotation(angle);
		GetSprite().move(towardsDirection*deltaTime);
	}

}
