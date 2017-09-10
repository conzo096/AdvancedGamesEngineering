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
	playButton.buttonSprite.setPosition(Game::Instance()->Game::GetScreenWidth() /2, Game::Instance()->Game::GetScreenHeight() / 3);

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.action = exitApplication;
	exitButton.buttonTexture.loadFromFile("Images/Buttons/MenuExit.png");
	exitButton.buttonSprite = sf::Sprite(exitButton.buttonTexture);
	exitButton.buttonSprite.setOrigin(float(exitButton.buttonTexture.getSize().x) / 2, float(exitButton.buttonTexture.getSize().y) / 2);
	exitButton.buttonSprite.setPosition(Game::Instance()->Game::GetScreenWidth() /2, 2*(Game::Instance()->Game::GetScreenHeight() /3));
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
		if (menuEvent.type == sf::Event::Resized)
		{
			// update the view to the new size of the window and keep the center
			//Game::Instance()->GetRenderWindow().setView(sf::View(Game::Instance()->GetRenderWindow().getView().getCenter(), sf::Vector2f((float)menuEvent.size.width, (float)menuEvent.size.height)));
//			Game::Instance()->SetScreenWidth(menuEvent.size.width);
//			Game::Instance()->SetScreenHeight(menuEvent.size.height);
			//Game::Instance()->GetRenderWindow().create(sf::VideoMode(800, 600,32), "Bacon", sf::Style::Default);
			//Game::Instance()->SetScreenWidth(800);
			//Game::Instance()->SetScreenHeight(600);
				//Game::Instance()->GetRenderWindow().setView(sf::View(sf::FloatRect(0,0,1000,1000)));
				return nothing;
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


