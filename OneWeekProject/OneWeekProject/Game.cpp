#include "Game.h"

Game::GameState Game::gameState = uninitialized;
sf::RenderWindow Game::mainWindow;
int Game::SCREEN_WIDTH = 1024;
int Game::SCREEN_HEIGHT = 768;

// The game set up.
void Game::Start()
{
	if (gameState != uninitialized)
		return;

	// Create the initial window.
	mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Week One Project!");
	// Change the game state to display the splash logo.
	gameState = showingSplashScreen;

	GameLoop();
}


// The main loop for the game occurs here.
void Game::GameLoop()
{
	sf::Event currentEvent;
	// While the application is still to run.
	while (gameState != exiting)
	{
		// Recieve a game event.
		mainWindow.pollEvent(currentEvent);
		// Check current game state and act accordingly.
		switch (gameState)
		{
			case showingSplashScreen:
			{
				ShowSplashScreen();
				break;
			}
			case showingMainMenu:
			{
				ShowMainMenu();
				break;
			}
			case showingGraphicsMenu:
			{
				ShowGraphicsMenu();
				break;
			}
			case paused:
			{
				ShowPauseScreen();
				break;
			}
			case playing:
			{
				UpdateGame(currentEvent);
				break;
			}
		}
	}
}

void Game::ShowSplashScreen()
{
	mainWindow.clear(sf::Color(0, 0, 255));
	sf::Text text;
	text.setPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 15);
	text.setf
	text.setString("SPLASH");
	text.setFillColor(sf::Color(0, 255, 0));
	text.scale(5, 5);
	mainWindow.draw(text);
	mainWindow.display();
	sf::Event currentEvent;
	
	// Move to main menu now.
	while (mainWindow.pollEvent(currentEvent))
	{
		if (currentEvent.type == sf::Event::EventType::KeyPressed
			|| currentEvent.type == sf::Event::EventType::MouseButtonPressed
			|| currentEvent.type == sf::Event::EventType::Closed)
		{
			gameState = showingMainMenu;
		}
	}
}

void Game::ShowMainMenu()
{

	//int result;
	//switch (result)
	//{
	//	case MainMenu::exit:
	//	{
	//		gameState = Game::Exiting;
	//		break;
	//	}
	//	case MainMenu::play:
	//	{
	//		gameState = Game::Playing;
	//		break;
	//	}
	//	case MainMenu::graphicsMenu:
	//	{
	//		ShowGraphicsMenu();
	//		break;
	//	}
	//}

	mainWindow.clear(sf::Color(0, 255, 0));
	sf::Text text;
	text.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/25);
	text.setString("MainMenu");
	mainWindow.draw(text);
	mainWindow.display();
	sf::Event currentEvent;
	while (mainWindow.pollEvent(currentEvent))
	{
		if (currentEvent.type == sf::Event::EventType::KeyPressed
			|| currentEvent.type == sf::Event::EventType::MouseButtonPressed
			|| currentEvent.type == sf::Event::EventType::Closed)
		{
			gameState = playing;
		}
	}
}

void Game::ShowPauseScreen()
{
	mainWindow.clear(sf::Color(0, 255, 255));
	sf::Text text;
	//text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	text.setString("Pause Menu");
	text.scale(5, 5);
	mainWindow.draw(text);
	mainWindow.display();
	sf::Event currentEvent;
	while (mainWindow.pollEvent(currentEvent))
	{
		if (currentEvent.type == sf::Event::EventType::KeyPressed
			|| currentEvent.type == sf::Event::EventType::MouseButtonPressed
			|| currentEvent.type == sf::Event::EventType::Closed)
		{
			gameState = playing;
		}
	}
}

void Game::ShowGraphicsMenu()
{
	sf::Text text;
	text.setPosition(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
	text.setString("GRAPHICSMENU");
	mainWindow.draw(text);
}

// This handles the actual game logic. What actually happens when the game
// is running. 
void Game::UpdateGame(sf::Event& currentEvent)
{
	mainWindow.clear(sf::Color(255 , 0, 0));
	sf::Text text;
	text.setPosition(sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
	text.setCharacterSize(50);
	text.setFillColor(sf::Color(0, 255, 0));
	text.setString("GAME GAME GAME");
	mainWindow.draw(text);
	mainWindow.display();
	if (currentEvent.type == sf::Event::Closed)
		gameState = Game::exiting;
	if (currentEvent.key.code == sf::Keyboard::Escape)
		gameState = Game::paused;
}