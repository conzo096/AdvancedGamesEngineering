#include "MainMenu.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

MainMenu::MainMenuOptions MainMenu::ShowMenu()
{
	MainMenuOptions optionSelected;
	switch (optionSelected)
	{
		case exitApplication:
		{
			return exitApplication;
		}
		case playGame:
		{
			return playGame;
		}
		case showGraphicsOption:
		{
			return showGraphicsOption;
		}
	}
}