#pragma once
#include "stdafx.h"
class MainMenu
{
public:

	enum MenuResult
	{
		exitApplication, playGame, showGraphicsOption, nothing
	};

	struct MenuItem
	{
	public:
		sf::Text text;
		MenuResult action;
	};


	MainMenu();
	~MainMenu();

	MenuResult Show(sf::RenderWindow& renderWindow);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	MenuResult HandleController();
	void DrawMenu(sf::RenderWindow& renderWindow);

	sf::Font textFont;
	std::vector<MenuItem> options;
	int tracker = 0;
};

