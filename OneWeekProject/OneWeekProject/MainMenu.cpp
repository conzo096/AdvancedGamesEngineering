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
	playButton.text.setPosition(Game::Game::GetScreenWidth() / 2, Game::Game::GetScreenHeight() / 4);
	playButton.text.setString("PLAY GAME!");
	if(sf::Joystick::isConnected(0))
		playButton.text.setFillColor(sf::Color::Blue);

	//Play menu item coordinates
	MenuItem optionsButton;
	optionsButton.action = showGraphicsOption;
	optionsButton.text.setFont(textFont);
	optionsButton.text.setPosition(Game::Game::GetScreenWidth() / 2, 2*(Game::Game::GetScreenHeight() / 4));
	optionsButton.text.setString("OPTIONS");

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.action = exitApplication;
	exitButton.text.setFont(textFont);
	exitButton.text.setPosition(Game::Game::GetScreenWidth() / 2, 3 * (Game::Game::GetScreenHeight() / 4));
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
		DrawMenu(renderWindow);
		renderWindow.pollEvent(menuEvent);
		if (menuEvent.type == sf::Event::MouseMoved)
		{
			for (MenuItem& o : options)
			{
				if (o.text.getGlobalBounds().contains(Game::GetRenderWindow().mapPixelToCoords(sf::Vector2i(menuEvent.mouseButton.x, menuEvent.mouseButton.y))))
					o.text.setFillColor(sf::Color::Blue);
			}
			DrawMenu(renderWindow);
		}
	
		MenuResult res = nothing;
		if (menuEvent.type == sf::Event::MouseButtonPressed)
		{
			res = HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
		}
		if (menuEvent.type == sf::Event::JoystickButtonPressed || menuEvent.type == sf::Event::JoystickMoved)
		{
			res = HandleController();
			DrawMenu(Game::GetRenderWindow());
		}
		if (res != nothing)
			return res;
	}


}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::vector<MenuItem>::iterator it;
	for (it = options.begin(); it != options.end(); it++)
	{
		sf::Text text = (*it).text;
		if (text.getGlobalBounds().contains(Game::GetRenderWindow().mapPixelToCoords(sf::Vector2i(x,y))))
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
	
		MenuResult res = options.at(tracker).action;
		// If it is, handle movement.
		float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		if (clock.getElapsedTime().asSeconds() > 0.25f)
		{
			// Set all font colours to white.
			clock.restart();
			if (y > 15)
			{
				tracker++;
				if (tracker > options.size()-1)
					tracker = 0;
				res = options.at(tracker).action;
				options.at(tracker).text.setFillColor(sf::Color::Blue);
				DrawMenu(Game::GetRenderWindow());
				return nothing;
			}
			else if (y < -15)
			{
				tracker--;
				if (tracker < 0)
					tracker = options.size() - 1;
				res = options.at(tracker).action;
				options.at(tracker).text.setFillColor(sf::Color::Blue);
				DrawMenu(Game::GetRenderWindow());
				return nothing;
			}
			for (int i = 0; i < options.size(); i++)
			{
				if (tracker == i)
					options.at(i).text.setFillColor(sf::Color::Blue);
				else
					options.at(i).text.setFillColor(sf::Color::White);
			}


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
	sprite.setScale(sf::Vector2f(float(image.getSize().x) / Game::GetScreenWidth(), float(image.getSize().y) / Game::GetScreenHeight()));


	renderWindow.draw(sprite);
	for (MenuItem o : options)
	{
		renderWindow.draw(o.text);
	}
	renderWindow.display();

}


