#include "PauseScreen.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Game.h"
#include <string>
PauseMenu::PauseMenu()
{
	textFont.loadFromFile("res/Fonts/Cracked Code.ttf");
	//Play menu item coordinates
	MenuItem playButton;
	playButton.action = keepPlaying;
	playButton.text.setFont(textFont);
	playButton.text.setPosition(Game::Game::GetScreenWidth() / 2, Game::Game::GetScreenHeight() / 5);
	playButton.text.setString("CONTINUE!");
	if (sf::Joystick::isConnected(0))
		playButton.text.setFillColor(sf::Color::Blue);

	//Play menu item coordinates
	MenuItem menuButton;
	menuButton.action = showMainMenu;
	menuButton.text.setFont(textFont);
	menuButton.text.setPosition(Game::Game::GetScreenWidth() / 2, 2 * (Game::Game::GetScreenHeight() / 5));
	menuButton.text.setString("MAIN MENU");

	options.push_back(playButton);
	options.push_back(menuButton);
}

PauseMenu::~PauseMenu()
{
}

PauseMenu::MenuResult PauseMenu::Show(sf::RenderWindow& renderWindow)
{

	DrawMenu(renderWindow);
	return GetMenuResponse(renderWindow);
}

PauseMenu::MenuResult PauseMenu::GetMenuResponse(sf::RenderWindow & renderWindow)
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
				if (o.text.getGlobalBounds().contains(Game::GetRenderWindow().mapPixelToCoords(sf::Vector2i(menuEvent.mouseButton.x, menuEvent.mouseButton.y))))
					o.text.setFillColor(sf::Color::Blue);
			}
		}

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
		DrawMenu(renderWindow);
	}


}

PauseMenu::MenuResult PauseMenu::HandleClick(int x, int y)
{
	std::vector<MenuItem>::iterator it;
	for (it = options.begin(); it != options.end(); it++)
	{
		sf::Text text = (*it).text;
		if (text.getGlobalBounds().contains(Game::GetRenderWindow().mapPixelToCoords(sf::Vector2i(x, y))))
		{

			return (*it).action;
		}
	}
	return nothing;
}

PauseMenu::MenuResult PauseMenu::HandleController()
{
	// Handle Controller options.
	if (sf::Joystick::isConnected(0))
	{
		if (clock.getElapsedTime().asSeconds() > 0.08f)
		{
			clock.restart();

			MenuResult res = options.at(tracker).action;
			// If it is, handle movement.
			float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
			if (y > 75)
			{
				options.at(tracker).text.setFillColor(sf::Color::White);

				tracker++;
				if (tracker > options.size() - 1)
					tracker = 0;
				res = options.at(tracker).action;
				options.at(tracker).text.setFillColor(sf::Color::Blue);
				DrawMenu(Game::GetRenderWindow());
				return nothing;
			}
			else if (y < -75)
			{
				options.at(tracker).text.setFillColor(sf::Color::White);
				tracker--;
				if (tracker < 0)
					tracker = options.size() - 1;
				res = options.at(tracker).action;
				options.at(tracker).text.setFillColor(sf::Color::Blue);
				DrawMenu(Game::GetRenderWindow());
				return nothing;
			}
			if (sf::Joystick::isButtonPressed(0, sf::Joystick::X))
			{
				return res;
			}
		}
	}
	return nothing;
}

void PauseMenu::DrawMenu(sf::RenderWindow & renderWindow)
{
	renderWindow.clear();

	//Load menu image from file
	/*sf::Texture image;
	image.loadFromFile("images/PauseMenu.png");
	sf::Sprite sprite(image);
	sprite.setScale(sf::Vector2f(float(image.getSize().x) / Game::GetScreenWidth(), float(image.getSize().y) / Game::GetScreenHeight()));
*/

//	renderWindow.draw(sprite);
	for (MenuItem o : options)
	{
		renderWindow.draw(o.text);
	}

	sf::Text score;
	score.setFont(textFont);
	score.setString(std::to_string(Game::GetGameManager().score));
	score.setPosition(Game::Game::GetScreenWidth() / 2, (50) + 2 * (Game::Game::GetScreenHeight() / 5));
	renderWindow.draw(score);
	for (int i=0; i < Game::GetScores().size();i++)
	{
		float O = Game::GetScores().at(i);
		sf::Text score;
		score.setFont(textFont);
		score.setString(std::to_string(O));
		score.setPosition(Game::Game::GetScreenWidth() / 2, (50+(i+1)*100) + (2 * (Game::Game::GetScreenHeight() / 5)));
		renderWindow.draw(score);
	}
	renderWindow.display();
	for (MenuItem o : options)
	{
		o.text.setFillColor(sf::Color::White);
	}
}


