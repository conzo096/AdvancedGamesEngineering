#include "Ship.h"



Ship::Ship()
{
}


Ship::~Ship()
{
}

void Ship::Draw(sf::RenderWindow& renderWindow)
{
	if (isActive)
	{
		renderWindow.draw(GetSprite());
		std::vector<Bullet*>::const_iterator itr = GetBullets().begin();
		while (itr != GetBullets().end())
		{
			(*itr)->Draw(renderWindow);
			itr++;
		}
	}
}