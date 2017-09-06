#include "Bullet.h"
#include "Game.h"


Bullet::Bullet()
{


}


Bullet::~Bullet()
{
}


void Bullet::Update(float deltaTime)
{
	sf::Vector2f pos = GetPosition();

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
	std::map<std::string, RenderableObject*>::const_iterator itr = Game::Instance()->GetGameManager().GetGameObjects().begin();
	while (itr != Game::Instance()->GetGameManager().GetGameObjects().end())
	{
		if (GetSprite().getGlobalBounds().intersects(itr->second->GetSprite().getGlobalBounds))
		{

		}
	}

	GetSprite().move(GetVelocity()*deltaTime);
}