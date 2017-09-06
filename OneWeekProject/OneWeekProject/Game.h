#pragma once
#include "stdafx.h"
#include "GameManager.h"
class Game
{
public:
	enum GameState
	{
		uninitialized, showingSplashScreen,paused,
		showingMainMenu, playing, exiting, showingGraphicsMenu
	};

	~Game();

	static Game *Instance()
	{
		if (!instance)
			instance = new Game();
		return instance;
	}
	GameState GetGameState()
	{
		return instance->gameState;
	}
	void SetGameState(GameState state)
	{
		instance->gameState = state;
	}
	int GetScreenWidth()
	{
		return instance->screenWidth;
	}
	void SetScreenWidth(int width)
	{
		instance->screenWidth = width;
	}
	int GetScreenHeight()
	{
		return instance->screenHeight;
	}
	void SetScreenHeight(int height)
	{
		instance->screenHeight = height;
	}
	sf::RenderWindow& GetRenderWindow()
	{
		return instance->mainWindow;
	}
	sf::Clock GetClock()
	{
		return instance->clock;
	}
	void SetClock(sf::Clock cl)
	{
		instance->clock = cl;
	}
	GameManager& GetGameManager()
	{
		return gameManager;
	}


	// Start the game engine.
	void Start();

private:
	
	// Singleton instance of the game engine.
	static Game *instance;

	Game();



	// What state the window is currently in.
	GameState gameState;
	// Width and height of the screen.
	int screenWidth;
	int screenHeight;
	// The window everything is rendered too.
	sf::RenderWindow mainWindow;
	// Clock to keep track of timings.
	sf::Clock clock;
	// Instance of the game manager.
	GameManager gameManager;
	// Loops, checking what game state it is in and acts
	// accordingly.
	void GameLoop(); 
	// Show the splash screen.
	void ShowSplashScreen();
	// Show the main menu of the game.
	void ShowMainMenu();
	// Display the pause screen.
	void ShowPauseScreen();
	// Show the graphics menu.
	void ShowGraphicsMenu();
	// Update the 'main game'.
	void UpdateGame(sf::Event& currentEvent);
};

