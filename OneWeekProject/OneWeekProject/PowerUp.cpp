#include "PowerUp.h"



PowerUp::PowerUp()
{
	LoadSprite("Images/GameObjects/PowerUp.png");
	spriteRect = sf::IntRect(0, 0, 32, 32);
	GetSprite().setTextureRect(spriteRect);

}


PowerUp::~PowerUp()
{
}

void PowerUp::Draw(sf::RenderWindow & window)
{
	if (isActive)
	{
		if (clock.getElapsedTime().asSeconds() > 0.25f)
		{
			if (spriteRect.left >= 96)
				spriteRect.left = 0;
			else
				spriteRect.left += 48;

			GetSprite().setTextureRect(spriteRect);
			clock.restart();
		}
		window.draw(GetSprite());
	}

}


