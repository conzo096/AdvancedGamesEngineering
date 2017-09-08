#include "PlayerShip.h"
#include "PowerUp.h"
#include "Game.h"
#include "PlayerBullet.h"

PlayerShip::PlayerShip():power()
{
	GetMaxVelocity() = sf::Vector2f(10,10);
	health = 100;
	isActive = true;
	fireRate = 0.25f;
	cooldown = 0.0f;
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
	if(cooldown >=0)
		cooldown -= deltaTime;

	if (power != NULL)
	{
		power->ReduceDuration(deltaTime);
		// If power up is over, remove the power up.
		if (power->GetDuration() == 0)
		{
			power->toBeDeleted = true;
			power = NULL;
		}
	}
	sf::Vector2f movement;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		//GetVelocity().y -= 1.0f;
		movement.y-=600;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//GetVelocity().y += 1.0f;
		movement.y+=600;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//GetVelocity().x -= 1.0f;
		movement.x-=600;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//GetVelocity().x += 1.0f;
		movement.x+=600;
	}

	sf::Vector2f pos = GetPosition();


	// Calculate if the move would result in ship being off screen.
	if (pos.x  < GetSprite().getScale().x
		|| pos.x >(Game::Instance()->GetScreenWidth()- GetSprite().getGlobalBounds().width))
	{
		movement.x = -movement.x; // Bounce by current velocity in opposite direction
	}
	if (pos.y  < GetSprite().getScale().y
		|| pos.y >(Game::Instance()->GetScreenHeight() - GetSprite().getGlobalBounds().height))
	{
		movement.y = -movement.y; // Bounce by current velocity in opposite direction
	}


	// Add limit to bullets created.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (cooldown <= 0)
		{
			if (power == NULL)
			{
				PlayerBullet* bullet = new PlayerBullet();
				bullet->LoadSprite("Images/GameObjects/Bullet.png");
				bullet->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width / 2), GetPosition().y - GetSprite().getGlobalBounds().height);
				bullet->GetVelocity() = sf::Vector2f(0, -600);
				Game::Instance()->GetGameManager().GetBullets().push_back(bullet);
			}
			else if (power != NULL)
			{
				if (power->GetPowerUpType() == PowerUp::dualCannons)
				{
					PlayerBullet* bullet = new PlayerBullet();
					bullet->LoadSprite("Images/GameObjects/Bullet.png");
					bullet->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width / 2), GetPosition().y - GetSprite().getGlobalBounds().height);
					bullet->GetVelocity() = sf::Vector2f(0, -bullet->speed);
					Game::Instance()->GetGameManager().GetBullets().push_back(bullet);

					PlayerBullet* bullet1 = new PlayerBullet();
					bullet1->LoadSprite("Images/GameObjects/Bullet.png");
					bullet1->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width / 2), GetPosition().y - GetSprite().getGlobalBounds().height);
					bullet1->GetVelocity() = sf::Vector2f(0, bullet1->speed);
					Game::Instance()->GetGameManager().GetBullets().push_back(bullet1);

				}
			}
			cooldown = fireRate;
		}
	}
	//Check to see if player intersects with any powerUp.
	for (auto it = Game::Instance()->GetGameManager().GetGameObjects().begin(); it != Game::Instance()->GetGameManager().GetGameObjects().end();)
	{

		if (strstr(it->first.c_str(), "Power") && GetSprite().getGlobalBounds().intersects(it->second->GetSprite().getGlobalBounds())   && it->second->isActive)
		{
				power = static_cast<PowerUp*>(it->second);
				it->second->isActive =false;
				break;
		}
		it++;
	}

	//GetSprite().move(GetVelocity()*deltaTime);
	GetSprite().move(movement*deltaTime);
}