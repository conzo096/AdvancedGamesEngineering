#include "PlayerBullet.h"
#include "Game.h"
#include "PowerUp.h"
#include "RangedEnemy.h"

PlayerBullet::PlayerBullet()
{
	damage = 30005;
	LoadSprite("Images/GameObjects/Bullet.png");
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
				RangedEnemy* enemy = static_cast<RangedEnemy*>
					(Game::Instance()->GetGameManager().Get(itr->first));
				enemy->AddHealth(-damage);
				// This bullet is to be deleted.
				toBeDeleted = true;
				if (enemy->GetHealth() <= 0)
				{

					Game::Instance()->GetGameManager().PlayClip("Audio/kaboom.wav");
					itr->second->toBeDeleted = true;
					if (rand() % 10 == 0)
					{
						PowerUp* power = new PowerUp();
						power->LoadSprite("Images/GameObjects/DualCannons.png");
						power->SetPosition(GetPosition().x, GetPosition().y);
						PowerUp::PowerUpType type = static_cast<PowerUp::PowerUpType>(rand() % 3);
						power->SetPowerUpType(type);
						power->SetDuration(5);
						Game::Instance()->GetGameManager().AddObject("PowerUpA", power);
					}
				}
			}
		}
		itr++;
	}

	GetSprite().move(velocity*deltaTime);

}
