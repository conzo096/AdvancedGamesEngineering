#include "MainMenu.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Game.h"

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
	sprite.setScale(sf::Vector2f(float(image.getSize().x) / Game::Instance()->GetScreenWidth(), float(image.getSize().y) / Game::Instance()->GetScreenHeight()));
	//Setup clickable regions

	//Play menu item coordinates
	MenuItem playButton;
	playButton.action = playGame;
	playButton.buttonTexture.loadFromFile("Images/Buttons/MenuStart.png");
	playButton.buttonSprite = sf::Sprite(playButton.buttonTexture);
	playButton.buttonSprite.setOrigin(float(playButton.buttonTexture.getSize().x) / 2, float(playButton.buttonTexture.getSize().y) / 2);
	playButton.buttonSprite.setPosition(Game::Instance()->Game::GetScreenWidth() /2, Game::Instance()->Game::GetScreenHeight() / 4);

	//Play menu item coordinates
	MenuItem graphicsOptions;
	graphicsOptions.action = showGraphicsOption;
	graphicsOptions.buttonTexture.loadFromFile("Images/Buttons/MenuStart.png");
	graphicsOptions.buttonSprite = sf::Sprite(graphicsOptions.buttonTexture);
	graphicsOptions.buttonSprite.setOrigin(float(graphicsOptions.buttonTexture.getSize().x) / 2, float(graphicsOptions.buttonTexture.getSize().y) / 2);
	graphicsOptions.buttonSprite.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, 2*(Game::Instance()->Game::GetScreenHeight()) / 4);

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.action = exitApplication;
	exitButton.buttonTexture.loadFromFile("Images/Buttons/MenuExit.png");
	exitButton.buttonSprite = sf::Sprite(exitButton.buttonTexture);
	exitButton.buttonSprite.setOrigin(float(exitButton.buttonTexture.getSize().x) / 2, float(exitButton.buttonTexture.getSize().y) / 2);
	exitButton.buttonSprite.setPosition(Game::Instance()->Game::GetScreenWidth() /2, 3*(Game::Instance()->Game::GetScreenHeight())/4);
	menuItems.push_back(playButton);
	menuItems.push_back(graphicsOptions);
	menuItems.push_back(exitButton);

	renderWindow.draw(sprite);
	renderWindow.draw(playButton.buttonSprite);
	renderWindow.draw(exitButton.buttonSprite);
	renderWindow.draw(graphicsOptions.buttonSprite);
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

		if (sprite.getGlobalBounds().contains(Game::Instance()->GetRenderWindow().mapPixelToCoords(sf::Vector2i(x,y))))
		{
			return (*it).action;
		}
	}
	return nothing;
}


