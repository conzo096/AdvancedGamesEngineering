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

	sf::Sprite& GetSprite()
	{
		return sprite;
	}

	void LoadSprite(std::string fileName)
	{
		if (texture.loadFromFile(fileName))
			sprite = sf::Sprite(texture);
	}
	void SetSprite(sf::Sprite spr)
	{
		sprite = spr;
	}

private:
	// Texture of the sprite.
	sf::Texture texture;
	// Physical object.
	sf::Sprite sprite;
	// 
	// Bounding box around the 2D object.
	sf::Rect<int> boundingBox;
	// Direction and speed of the object.
	sf::Vector2f velocity;
	// Condition to check status of the game object.
	bool isActive;
	// Time the object has been alive.
	float timeActive;
};

