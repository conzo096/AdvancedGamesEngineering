#include "PlayerShip.h"
#include "PowerUp.h"
#include "Game.h"
#include "PlayerBullet.h"
#include <iostream>
PlayerShip::PlayerShip():power()
{
	GetMaxVelocity() = sf::Vector2f(10,10);
	health = 250;
	isActive = true;
	fireRate = 0.25f;
	cooldown = 0.0f;
	LoadSprite("res/Images/GameObjects/PlayerShip.png");
	GetSprite().setOrigin(sf::Vector2f(float(GetSprite().getTexture()->getSize().x) / 2, float(GetSprite().getTexture()->getSize().y) / 2));
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
	if (health <= 0)
	{
		toBeDeleted = true;
		//delete power;
	//	Game::ResetGame();
	}
	if (power != NULL)
	{
		power->ReduceDuration(deltaTime);
		// If power up is over, remove the power up.
		if (power->GetDuration() <= 0)
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

	// Check if controller is connected.
	if (sf::Joystick::isConnected(0))
	{
		// If it is, handle movement.
		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		if (x >15 || x <-15)
			movement.x += x*5;
		float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		if (y >15 || y<-15)
			movement.y = y*5;

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) < -15)
		{
			if (cooldown <= 0)
			{
				if (power == NULL)
				{
					PlayerBullet* bullet = new PlayerBullet();
					bullet->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width / 2), GetPosition().y - GetSprite().getGlobalBounds().height);
					bullet->GetVelocity() = sf::Vector2f(0, -600);
					Game::GetGameManager().GetBullets().push_back(bullet);
				}
				else if (power != NULL)
				{
					if (power->GetPowerUpType() == PowerUp::dualCannons)
					{
						PlayerBullet* bullet = new PlayerBullet();
						bullet->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width), GetPosition().y - GetSprite().getGlobalBounds().height);
						bullet->GetVelocity() = sf::Vector2f(0, -bullet->speed);
						Game::GetGameManager().GetBullets().push_back(bullet);

						PlayerBullet* bullet1 = new PlayerBullet();
						bullet1->SetPosition(GetPosition().x - (GetSprite().getGlobalBounds().width), GetPosition().y - GetSprite().getGlobalBounds().height);
						bullet1->GetVelocity() = sf::Vector2f(0, -bullet1->speed);
						Game::GetGameManager().GetBullets().push_back(bullet1);
					}
					else if (power->GetPowerUpType() == PowerUp::tripleCannons)
					{
						PlayerBullet* bullet = new PlayerBullet();
						bullet->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width / 2), GetPosition().y - GetSprite().getGlobalBounds().height);
						bullet->GetVelocity() = sf::Vector2f(0, -bullet->speed);
						Game::GetGameManager().GetBullets().push_back(bullet);

						PlayerBullet* bullet1 = new PlayerBullet();
						bullet1->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width), GetPosition().y - GetSprite().getGlobalBounds().height);
						bullet1->GetVelocity() = sf::Vector2f(0, -bullet1->speed);
						Game::GetGameManager().GetBullets().push_back(bullet1);

						PlayerBullet* bullet2 = new PlayerBullet();
						bullet2->SetPosition(GetPosition().x - (GetSprite().getGlobalBounds().width), GetPosition().y - GetSprite().getGlobalBounds().height);
						bullet2->GetVelocity() = sf::Vector2f(0, -bullet2->speed);
						Game::GetGameManager().GetBullets().push_back(bullet2);
					}
					else if (power->GetPowerUpType() == PowerUp::none)
					{
						Game::GetGameManager().PlayClip("res/Audio/outtaAmmo.wav");
					}
				}
				cooldown = fireRate;
			}
		}
	}


	sf::Vector2f pos = GetPosition();
	sf::FloatRect bounds(sf::Vector2f(0.f, 0.f), sf::Vector2f(Game::GetRenderWindow().getView().getSize().x, Game::GetRenderWindow().getView().getSize().y));

	//// Calculate if the move would result in ship being off screen.
	if (pos.x < bounds.left)
	{
		movement.x +=650;
	}
	if(pos.x > bounds.width - GetSprite().getGlobalBounds().width)
	{
		movement.x -= 650;
	}

	if (pos.y < bounds.top)
	{
		movement.y += 650;
	}
	if(pos.y > bounds.height - GetSprite().getGlobalBounds().height)
	{
		movement.y -=650;
	}

	// Add limit to bullets created.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (cooldown <= 0)
		{
			if (power == NULL)
			{
				PlayerBullet* bullet = new PlayerBullet();
				bullet->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width / 2), GetPosition().y - GetSprite().getGlobalBounds().height);
				bullet->GetVelocity() = sf::Vector2f(0, -600);
				Game::GetGameManager().GetBullets().push_back(bullet);
			}
			else if (power != NULL)
			{
				if (power->GetPowerUpType() == PowerUp::dualCannons)
				{
					PlayerBullet* bullet = new PlayerBullet();
					bullet->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width), GetPosition().y - GetSprite().getGlobalBounds().height);
					bullet->GetVelocity() = sf::Vector2f(0, -bullet->speed);
					Game::GetGameManager().GetBullets().push_back(bullet);

					PlayerBullet* bullet1 = new PlayerBullet();
					bullet1->SetPosition(GetPosition().x - (GetSprite().getGlobalBounds().width), GetPosition().y - GetSprite().getGlobalBounds().height);
					bullet1->GetVelocity() = sf::Vector2f(0, -bullet1->speed);
					Game::GetGameManager().GetBullets().push_back(bullet1);
				}
				else if (power->GetPowerUpType() == PowerUp::tripleCannons)
				{
					PlayerBullet* bullet = new PlayerBullet();
					bullet->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width/2), GetPosition().y - GetSprite().getGlobalBounds().height);
					bullet->GetVelocity() = sf::Vector2f(0, -bullet->speed);
					Game::GetGameManager().GetBullets().push_back(bullet);

					PlayerBullet* bullet1 = new PlayerBullet();
					bullet1->SetPosition(GetPosition().x + (GetSprite().getGlobalBounds().width), GetPosition().y - GetSprite().getGlobalBounds().height);
					bullet1->GetVelocity() = sf::Vector2f(0, -bullet1->speed);
					Game::GetGameManager().GetBullets().push_back(bullet1);

					PlayerBullet* bullet2 = new PlayerBullet();
					bullet2->SetPosition(GetPosition().x - (GetSprite().getGlobalBounds().width), GetPosition().y - GetSprite().getGlobalBounds().height);
					bullet2->GetVelocity() = sf::Vector2f(0, -bullet2->speed);
					Game::GetGameManager().GetBullets().push_back(bullet2);
				}
				else if (power->GetPowerUpType() == PowerUp::none)
				{
					Game::GetGameManager().PlayClip("res/Audio/outtaAmmo.wav");
				}
			}
			cooldown = fireRate;
		}
	}
	//Check to see if player intersects with any powerUp.
	for (auto it = Game::GetGameManager().GetGameObjects().begin(); it != Game::GetGameManager().GetGameObjects().end();)
	{

		if (strstr(it->first.c_str(), "Power") && GetSprite().getGlobalBounds().intersects(it->second->GetSprite().getGlobalBounds())   && it->second->isActive)
		{
			if (power != NULL)
			{
				power->SetDuration(0);
				power->toBeDeleted = true;
				power = NULL;
			}
			power = static_cast<PowerUp*>(it->second);
			it->second->isActive =false;
			break;
		}
		it++;
	}

	GetSprite().move(movement*deltaTime);
}