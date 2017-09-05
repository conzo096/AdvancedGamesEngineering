#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
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
	static GameState GetGameState()
	{
		return instance->gameState;
	}
	static void SetGameState(GameState state)
	{
		instance->gameState = state;
	}
	static int GetScreenWidth()
	{
		return instance->screenWidth;
	}
	static void SetScreenWidth(int width)
	{
		instance->screenWidth = width;
	}
	static int GetScreenHeight()
	{
		return instance->screenHeight;
	}
	static void SetScreenHeight(int height)
	{
		instance->screenHeight = height;
	}
	static sf::RenderWindow& GetRenderWindow()
	{
		return instance->mainWindow;
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

