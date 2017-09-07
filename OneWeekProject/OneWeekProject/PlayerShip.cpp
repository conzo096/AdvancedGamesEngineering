#include "PlayerShip.h"
#include "PowerUp.h"
#include "Game.h"

PlayerShip::PlayerShip():power(PowerUp::none)
{
	GetMaxVelocity() = sf::Vector2f(10,10);
	health = 100;
	isActive = true;
}


PlayerShip::~PlayerShip()
{

}

void RenderableObject::SetPosition(float x, float y)
{
		sprite.setPosition(x, y);
}

sf::Vector2f RenderableObject::GetPosition() const
{
		return sprite.getPosition();
}


void PlayerShip::Update(float deltaTime)
{
	timeActive += deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		GetVelocity().y -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		GetVelocity().y += 0.5f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		GetVelocity().x -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		GetVelocity().x += 1.0f;
	}

	sf::Vector2f pos = GetPosition();

	// Calculate if the move would result in ship being off screen.
	if (pos.x  < GetSprite().getScale().x
		|| pos.x >(Game::Instance()->GetScreenWidth()- GetSprite().getGlobalBounds().width))
	{
		GetVelocity().x = -GetVelocity().x; // Bounce by current velocity in opposite direction
	}
	if (pos.y  < GetSprite().getScale().y
		|| pos.y >(Game::Instance()->GetScreenHeight() - GetSprite().getGlobalBounds().height))
	{
		GetVelocity().y = -GetVelocity().y; // Bounce by current velocity in opposite direction
	}

	// Add limit to bullets created.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Bullet* bullet = new Bullet();
		bullet->LoadSprite("Images/GameObjects/Bullet.png");
		bullet->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width/2), GetPosition().y- GetSprite().getGlobalBounds().height);
		bullet->GetVelocity() = sf::Vector2f(0, -600);
		//bullets.push_back(bullet);
		Game::Instance()->GetGameManager().GetBullets().push_back(bullet);
	}


	GetSprite().move(GetVelocity()*deltaTime);

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

}