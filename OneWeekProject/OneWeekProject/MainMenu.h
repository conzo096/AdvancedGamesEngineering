#pragma once
class MainMenu
{
public:

	enum MainMenuOptions
	{
		exitApplication, playGame, showGraphicsOption
	};

	MainMenu();
	~MainMenu();

	MainMenuOptions ShowMenu();
};

