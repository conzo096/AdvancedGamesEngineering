#include "MainMenu.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Game.h"

MainMenu::MainMenu()
{
	textFont.loadFromFile("Fonts/Cracked Code.ttf");
	//Play menu item coordinates
	MenuItem playButton;
	playButton.action = playGame;
	playButton.text.setFont(textFont);
	playButton.text.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, Game::Instance()->Game::GetScreenHeight() / 4);
	playButton.text.setString("PLAY GAME!");
	if(sf::Joystick::isConnected(0))
		playButton.text.setFillColor(sf::Color::Blue);

	//Play menu item coordinates
	MenuItem optionsButton;
	optionsButton.action = showGraphicsOption;
	optionsButton.text.setFont(textFont);
	optionsButton.text.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, 2*(Game::Instance()->Game::GetScreenHeight() / 4));
	optionsButton.text.setString("OPTIONS");

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.action = exitApplication;
	exitButton.text.setFont(textFont);
	exitButton.text.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, 3 * (Game::Instance()->Game::GetScreenHeight() / 4));
	exitButton.text.setString("EXIT GAME");

	options.push_back(playButton);
	options.push_back(optionsButton);
	options.push_back(exitButton);
}


MainMenu::~MainMenu()
{
}

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& renderWindow)
{

	DrawMenu(renderWindow);
	return GetMenuResponse(renderWindow);
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow & renderWindow)
{
	// Keeping looping until a user choice has been made.
	sf::Event menuEvent;
	while (true)
	{
		renderWindow.pollEvent(menuEvent);
		if (menuEvent.type == sf::Event::MouseMoved)
		{
			for (MenuItem& o : options)
			{
				if (o.text.getGlobalBounds().contains(menuEvent.mouseMove.x, menuEvent.mouseMove.y))
					o.text.setFillColor(sf::Color::Blue);
			}
			DrawMenu(renderWindow);
		}
		if (menuEvent.type == sf::Event::MouseButtonPressed)
		{
			return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
		}
		if (menuEvent.type == sf::Event::Closed)
		{
			return exitApplication;
		}

		renderWindow.pollEvent(menuEvent);
		MenuResult res = nothing;
		if (menuEvent.type == sf::Event::MouseButtonPressed)
		{
			res = HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
		}
		if (menuEvent.type == sf::Event::JoystickButtonPressed || menuEvent.type == sf::Event::JoystickMoved)
		{
			res = HandleController();
		}
		if (res != nothing)
			return res;
	}
	return nothing;
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::vector<MenuItem>::iterator it;

	for (it = options.begin(); it != options.end(); it++)
	{
		sf::Text text = (*it).text;

		if (text.getGlobalBounds().contains(Game::Instance()->GetRenderWindow().mapPixelToCoords(sf::Vector2i(x, y))))
		{
			return (*it).action;
		}
	}

	return nothing;
}

MainMenu::MenuResult MainMenu::HandleController()
{
	// Handle Controller options.
	if (sf::Joystick::isConnected(0))
	{
		// Set all font colours to white.
		for (int i = 0; i < options.size(); i++)
			options.at(i).text.setFillColor(sf::Color::White);
		MenuResult res = options.at(tracker).action;
		// If it is, handle movement.
		float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		if (y > 15)
		{
			tracker++;
			if (tracker > options.size() - 1)
				tracker = 0;
			res = options.at(tracker).action;
			options.at(tracker).text.setFillColor(sf::Color::Blue);
			DrawMenu(Game::Instance()->GetRenderWindow());
			return nothing;
		}
		else if (y < -15)
		{
			tracker--;
			if (tracker < 0)
				tracker = options.size() - 1;
			res = options.at(tracker).action;
			options.at(tracker).text.setFillColor(sf::Color::Blue);
			DrawMenu(Game::Instance()->GetRenderWindow());
			return nothing;
		}

		if (sf::Joystick::isButtonPressed(0, sf::Joystick::Z))
		{
			return res;
		}
	}
	return nothing;
}

void MainMenu::DrawMenu(sf::RenderWindow & renderWindow)
{
	renderWindow.clear();

	//Load menu image from file
	sf::Texture image;
	image.loadFromFile("images/MainMenu.png");
	sf::Sprite sprite(image);
	sprite.setScale(sf::Vector2f(float(image.getSize().x) / Game::Instance()->GetScreenWidth(), float(image.getSize().y) / Game::Instance()->GetScreenHeight()));


	renderWindow.draw(sprite);
	for (MenuItem o : options)
	{
		renderWindow.draw(o.text);
	}
	renderWindow.display();
	for (MenuItem o : options)
	{
			o.text.setFillColor(sf::Color::White);
	}
}


