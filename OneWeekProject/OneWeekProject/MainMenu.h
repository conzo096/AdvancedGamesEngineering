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
		sf::Rect<int> rect;
		MenuResult action;
	};


	MainMenu();
	~MainMenu();

	MenuResult Show(sf::RenderWindow& renderWindow);
private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> menuItems;
};

