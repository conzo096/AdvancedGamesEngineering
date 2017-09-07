#include "RangedEnemy.h"
#include "PlayerShip.h"
#include "Game.h"

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
	sf::Vector2f playerPosition = player->GetPosition();
	//Move towards player.
	sf::Vector2f towardsDirection = playerPosition - GetPosition();


	if ((int)timeActive % 5 == 0)
	{
		Bullet* bullet = new Bullet();
		bullet->LoadSprite("Images/GameObjects/Bullet.png");
		bullet->belongsTo = GetName();
		bullet->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width / 2), GetPosition().y - GetSprite().getGlobalBounds().height);
		bullet->GetVelocity() = sf::Vector2f(towardsDirection);
		bullets.push_back(bullet);
	}

	// Update all the bullets.
	std::vector<Bullet*>::iterator itr = GetBullets().begin();
	while (itr != GetBullets().end())
	{
		if ((*itr)->toBeDeleted == false)
			(*itr)->Update(deltaTime);
		else
		{
			GetBullets().erase(itr);
			break;
		}
		itr++;
	}

	GetSprite().move(towardsDirection*deltaTime);


}
