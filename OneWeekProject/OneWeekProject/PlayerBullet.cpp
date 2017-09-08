#include "PlayerBullet.h"
#include "Game.h"


PlayerBullet::PlayerBullet()
{
}


PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Update(float deltaTime)
{

	sf::Vector2f pos = GetPosition();
	timeActive += deltaTime;

	// Remove after a short period of time.
	if (timeActive > 2.0f)
	{
		toBeDeleted = true;
		return;
	}
	// Calculate if the move would result in ship being off screen.
	if (pos.x  < GetSprite().getScale().x
		|| pos.x >(Game::Instance()->GetScreenWidth() - GetSprite().getGlobalBounds().width))
	{
		isActive = false;
	}
	if (pos.y  < GetSprite().getScale().y
		|| pos.y >(Game::Instance()->GetScreenHeight() - GetSprite().getGlobalBounds().height))
	{
		isActive = false;
	}

	//Check if it collides with the any object in game manger.
	std::map<std::string, RenderableObject*>::iterator itr = Game::Instance()->GetGameManager().GetGameObjects().begin();
	while (itr != Game::Instance()->GetGameManager().GetGameObjects().end())
	{
		// Remove elements while iterating
		if (GetSprite().getGlobalBounds().intersects(itr->second->GetSprite().getGlobalBounds()))
		{
			if (strstr(itr->first.c_str(), "Enemy"))
			{
				// This bullet is to be deleted.
				toBeDeleted = true;
				itr->second->toBeDeleted = true;
			}
		}
		itr++;
	}

	GetSprite().move(velocity*deltaTime);

}
