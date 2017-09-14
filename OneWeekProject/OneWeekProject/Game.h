#pragma once
#include "stdafx.h"
#include "GameManager.h"
#include "SFML/Audio.hpp"
class Game
{
public:
	enum GameState
	{
		uninitialized, showingSplashScreen,paused,
		showingMainMenu, playing, exiting, showingGraphicsMenu, gameOver
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
	static sf::Clock GetClock()
	{
		return instance->clock;
	}
	static void SetClock(sf::Clock cl)
	{
		instance->clock = cl;
	}
	static GameManager& GetGameManager()
	{
		return instance->gameManager;
	}

	static sf::View GetView()
	{
		return instance->view;
	}
	static void SetView(sf::View v)
	{
		instance->view = v;
	}

	static void AddScore(float score)
	{
		instance->highScores.push_back(score);
	}

	static std::vector<float> GetScores()
	{
		return instance->highScores;
	}

	// Start the game engine.
	void Start();
	//Reset the game.
	void ResetGame();
private:
	
	// Singleton instance of the game engine.
	static Game *instance;

	Game();



	// What state the window is currently in.
	GameState gameState;
	// View
	sf::View view;
	// Width and height of the screen.
	int screenWidth;
	int screenHeight;
	// The window everything is rendered too.
	sf::RenderWindow mainWindow;
	// Clock to keep track of timings.
	sf::Clock clock;
	// Instance of the game manager.
	GameManager gameManager;
	// Keep track of scores for the session.
	std::vector<float> highScores;


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
	// Show game over screen.
	void ShowGameOver();
	// Update the 'main game'.
	void UpdateGame();
};

