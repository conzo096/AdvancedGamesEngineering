#include "EnemyBullet.h"
#include "PlayerShip.h"
#include "Game.h"


EnemyBullet::EnemyBullet()
{
	damage = 20;
}


EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Update(float deltaTime)
{

	sf::Vector2f pos = GetPosition();
	timeActive += deltaTime;

	// Remove after a short period of time.
	if (timeActive > 2.0f)
	{
		toBeDeleted = true;
		isActive = false;
		return;
	}
	// Calculate if the move would result in ship being off screen.
	if (pos.x  < GetSprite().getScale().x
		|| pos.x >(Game::GetScreenWidth() - GetSprite().getGlobalBounds().width))
	{
		isActive = false;
		toBeDeleted = true;
	}
	if (pos.y  < GetSprite().getScale().y
		|| pos.y >(Game::GetScreenHeight() - GetSprite().getGlobalBounds().height))
	{
		isActive = false;
		toBeDeleted = true;
	}


	PlayerShip* player = static_cast<PlayerShip*>(Game::GetGameManager().Get("Player"));
	if(player != NULL)
	{
		// Remove elements while iterating
		if (GetSprite().getGlobalBounds().intersects(player->GetSprite().getGlobalBounds()) && !player->toBeDeleted)
		{
				// This bullet is to be deleted.
				toBeDeleted = true;
				player->AddHealth(-damage);
				return;
		}
	}
	else
	{
		return;
	}

	GetSprite().move(velocity*deltaTime);

}
