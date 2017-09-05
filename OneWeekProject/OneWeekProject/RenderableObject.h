#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
class RenderableObject
{
public:
	RenderableObject();
	~RenderableObject();

	// Update the game object.
	virtual void Update(float deltaTime);
	// Draw the game object.
	void Draw(sf::RenderWindow& renderWindow);

private:
	// Visual image of the game object.
	sf::Sprite sprite;
	// Bounding box around the 2D object.
	sf::Rect<int> boundingBox;
	// Direction and speed of the object.
	sf::Vector2f velocity;
	// Condition to check status of the game object.
	bool isActive;
	// Time the object has been alive.
	float timeActive;
};

