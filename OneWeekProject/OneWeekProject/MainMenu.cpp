#include "MainMenu.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& renderWindow)
{
	//Load menu image from file
	sf::Texture image;
	image.loadFromFile("images/MainMenu.png");
	sf::Sprite sprite(image);
	//Setup clickable regions

	//Play menu item coordinates
	MenuItem playButton;
	playButton.action = playGame;
	playButton.buttonTexture.loadFromFile("Images/Buttons/MenuStart.png");
	playButton.buttonSprite = sf::Sprite(playButton.buttonTexture);
	playButton.buttonSprite.setPosition(float(renderWindow.getSize().x)/2, float(renderWindow.getSize().y) / 3);

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.action = exitApplication;
	exitButton.buttonTexture.loadFromFile("Images/Buttons/MenuExit.png");
	exitButton.buttonSprite = sf::Sprite(exitButton.buttonTexture);
	exitButton.buttonSprite.setPosition(float(renderWindow.getSize().x)/2, 2*(float(renderWindow.getSize().y)/3));
	menuItems.push_back(playButton);
	menuItems.push_back(exitButton);

	renderWindow.draw(sprite);
	renderWindow.draw(playButton.buttonSprite);
	renderWindow.draw(exitButton.buttonSprite);
	renderWindow.display();

	return GetMenuResponse(renderWindow);
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow & renderWindow)
{
	// Keeping looping until a user choice has been made.
	sf::Event menuEvent;
	while (true)
	{
		renderWindow.pollEvent(menuEvent);
		if (menuEvent.type == sf::Event::MouseButtonPressed)
		{
			return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
		}
		if (menuEvent.type == sf::Event::Closed)
		{
			return exitApplication;
		}
	}
	return nothing;
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = menuItems.begin(); it != menuItems.end(); it++)
	{
		sf::Sprite sprite = (*it).buttonSprite;
		
		if (sprite.getGlobalBounds().contains(sf::Vector2f(x, y)))
		{
			return (*it).action;
		}
	}
	return nothing;
}


