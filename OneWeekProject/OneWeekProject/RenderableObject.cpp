#include "RenderableObject.h"



RenderableObject::RenderableObject(): velocity(sf::Vector2f(0,0))
{
}


RenderableObject::~RenderableObject()
{
}


void RenderableObject::Update(float deltaTime)
{
}

void RenderableObject::Draw(sf::RenderWindow& renderWindow)
{
	if(isActive)
		renderWindow.draw(sprite);
}
