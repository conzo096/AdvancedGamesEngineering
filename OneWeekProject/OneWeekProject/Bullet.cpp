#include "Bullet.h"
#include "Game.h"
#include <iostream>

Bullet::Bullet()
{


}


Bullet::~Bullet()
{
}


void Bullet::Update(float deltaTime)
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
			if (itr->first != "Player" || itr->first != belongsTo)
			{
				Game::Instance()->GetGameManager().enemiesAlive--;
				toBeDeleted = true;
				itr->second->toBeDeleted = true;
				break;
			}
		}
		itr++;
	}


	GetSprite().move(GetVelocity()*deltaTime);
}