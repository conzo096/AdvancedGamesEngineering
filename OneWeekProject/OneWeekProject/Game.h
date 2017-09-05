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

	Game();
	~Game();

	// Start the game engine.
	static void Start();

private:
	// What state the window is currently in.
	static GameState gameState;
	// Width and height of the screen.
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	// The window everything is rendered too.
	static sf::RenderWindow mainWindow;


	// Loops, checking what game state it is in and acts
	// accordingly.
	static void GameLoop(); 
	// Show the splash screen.
	static void ShowSplashScreen();
	// Show the main menu of the game.
	static void ShowMainMenu();
	// Display the pause screen.
	static void ShowPauseScreen();
	// Show the graphics menu.
	static void ShowGraphicsMenu();
	// Update the 'main game'.
	static void UpdateGame(sf::Event& currentEvent);

};

