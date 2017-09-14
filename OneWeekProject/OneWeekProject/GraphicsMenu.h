#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
class GraphicsOption
{
public:

	enum MenuResult
	{
		exitMenu, defaultResolution, resolutionOne, enableFullScreen, disableFullScreen, nothing
	};

	struct OptionItem
	{
	public:
		sf::Text text;
		MenuResult action;
	};

	GraphicsOption();
	~GraphicsOption();

	MenuResult Show(sf::RenderWindow& renderWindow);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	MenuResult HandleController();
	void DrawMenu(sf::RenderWindow& renderWindow);

	sf::Font textFont;
	std::vector<OptionItem> options;
	int tracker = 0;
	sf::Clock clock;
};

