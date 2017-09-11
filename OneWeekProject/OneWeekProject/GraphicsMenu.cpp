#include "GraphicsMenu.h"
#include "Game.h"


GraphicsOption::GraphicsOption()
{
	textFont.loadFromFile("Fonts/Cracked Code.ttf");
}


GraphicsOption::~GraphicsOption()
{
}

GraphicsOption::MenuResult GraphicsOption::Show(sf::RenderWindow & renderWindow)
{
	DrawMenu(renderWindow);
	return GetMenuResponse(renderWindow);
}

GraphicsOption::MenuResult GraphicsOption::GetMenuResponse(sf::RenderWindow & renderWindow)
{
	// Keeping looping until a user choice has been made.
	sf::Event menuEvent;
	while (true)
	{
		renderWindow.pollEvent(menuEvent);
		MenuResult res = nothing;
		if (menuEvent.type == sf::Event::MouseButtonPressed)
		{
			res = HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
		}
		if (menuEvent.type == sf::Event::Closed)
		{
			return exitMenu;
		}
		// Handle option changes.
		if (res == defaultResolution)
		{
			renderWindow.setSize(sf::Vector2u(1920, 1080));
			DrawMenu(renderWindow);
		}
		if (res == resolutionOne)
		{
			renderWindow.setSize(sf::Vector2u(800, 600));
			DrawMenu(renderWindow);
		}
		if (res == enableFullScreen)
		{
			renderWindow.create(sf::VideoMode(renderWindow.getSize().x, renderWindow.getSize().y, 32), "Week one project", sf::Style::Fullscreen);
			DrawMenu(renderWindow);
		}
		if (res == disableFullScreen)
		{
			renderWindow.create(sf::VideoMode(renderWindow.getSize().x, renderWindow.getSize().y, 32), "Week one project");
			DrawMenu(renderWindow);
		}
		if (res == exitMenu)
		{
			return exitMenu;
		}
	}
	return nothing;
}

GraphicsOption::MenuResult GraphicsOption::HandleClick(int x, int y)
{
	std::list<OptionItem>::iterator it;

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

void GraphicsOption::DrawMenu(sf::RenderWindow& renderWindow)
{
	renderWindow.clear();
	OptionItem option;
	option.action = defaultResolution;
	option.text.setFont(textFont);
	option.text.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, Game::Instance()->Game::GetScreenHeight() / 6);
	option.text.setString("1920 X 1080");

	OptionItem option1;
	option1.action = resolutionOne;
	option1.text.setFont(textFont);
	option1.text.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, 2 * (Game::Instance()->Game::GetScreenHeight() / 6));
	option1.text.setString("800 X 600");

	OptionItem option2;
	option2.action = enableFullScreen;
	option2.text.setFont(textFont);
	option2.text.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, 3*(Game::Instance()->Game::GetScreenHeight() / 6));
	option2.text.setString("ENABLE FULLSCREEN");

	OptionItem option3;
	option3.action = disableFullScreen;
	option3.text.setFont(textFont);
	option3.text.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, 4*(Game::Instance()->Game::GetScreenHeight() / 6));
	option3.text.setString("DISABLE FULLSCREEN");

	OptionItem option4;
	option4.action = exitMenu;
	option4.text.setFont(textFont);
	option4.text.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, 5*(Game::Instance()->Game::GetScreenHeight() / 6));
	option4.text.setString("EXIT");

	options.push_back(option);
	options.push_back(option1);
	options.push_back(option2);
	options.push_back(option3);
	options.push_back(option4);
	//Load menu image from file
	sf::Texture image;
	image.loadFromFile("images/GraphicsMenu.png");
	sf::Sprite sprite(image);
	sprite.setScale(sf::Vector2f(float(image.getSize().x) / Game::Instance()->GetScreenWidth(), float(image.getSize().y) / Game::Instance()->GetScreenHeight()));


	renderWindow.draw(sprite);
	for (OptionItem o : options)
	{
		renderWindow.draw(o.text);
	}
	renderWindow.display();
}