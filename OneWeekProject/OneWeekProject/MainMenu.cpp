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
	playButton.rect.top = 145;
	playButton.rect.left = 0;
	playButton.rect.width = 0;
	playButton.rect.height = 0;
	playButton.action = playGame;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.top = 0;
	exitButton.rect.left = 1023;
	exitButton.rect.width = 383;
	exitButton.rect.height = 560;
	exitButton.action = exitApplication;

	menuItems.push_back(playButton);
	menuItems.push_back(exitButton);

	renderWindow.draw(sprite);
	renderWindow.display();

	return GetMenuResponse(renderWindow);
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow & renderWindow)
{
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
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.width > y
			&& menuItemRect.top < y
			&& menuItemRect.left < x
			&& menuItemRect.width > x)
		{
			return (*it).action;
		}
	}
	return nothing;
}


