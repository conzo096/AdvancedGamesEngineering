#pragma once
#include "stdafx.h"
class GameOverScreen
{
public:

	enum MenuResult
	{
		showMainMenu, nothing, exit
	};

	struct MenuItem
	{
	public:
		sf::Text text;
		MenuResult action;
	};


	GameOverScreen();
	~GameOverScreen();

	MenuResult Show(sf::RenderWindow& renderWindow);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	MenuResult HandleController();
	void DrawMenu(sf::RenderWindow& renderWindow);

	sf::Font textFont;
	std::vector<MenuItem> options;
	int tracker = 0;
	sf::Clock clock;
};

