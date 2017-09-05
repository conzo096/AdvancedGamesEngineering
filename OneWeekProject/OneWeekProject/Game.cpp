#include "Game.h"
#include "stdafx.h"

Game *Game::instance = 0;


Game::Game() : screenWidth(1024), screenHeight(768), gameState(uninitialized)
{
}
Game::~Game()
{
}


// The game set up.
void Game::Start()
{
	if (GetGameState() != uninitialized)
		return;

	// Create the initial window.
	GetRenderWindow().create(sf::VideoMode(GetScreenWidth(), GetScreenHeight(), 32), "Week One Project!");
	// Change the game state to display the splash logo.
	SetGameState(showingSplashScreen);
	GameLoop();
}


// The main loop for the game occurs here.
void Game::GameLoop()
{
	sf::Event currentEvent;
	// While the application is still to run.
	while (GetGameState() != exiting)
	{
		// Recieve a game event.
		GetRenderWindow().pollEvent(currentEvent);
		// Check current game state and act accordingly.
		switch (GetGameState())
		{
			case showingSplashScreen:
			{
				Instance()->ShowSplashScreen();
				break;
			}
			case showingMainMenu:
			{
				Instance()->ShowMainMenu();
				break;
			}
			case showingGraphicsMenu:
			{
				Instance()->ShowGraphicsMenu();
				break;
			}
			case paused:
			{
				Instance()->ShowPauseScreen();
				break;
			}
			case playing:
			{
				Instance()->UpdateGame(currentEvent);
				break;
			}
		}
	}
}

// Displays the splash screen state.
void Game::ShowSplashScreen()
{
	GetRenderWindow().clear(sf::Color(0, 0, 255));
	
	sf::Texture texture;

	if(!texture.loadFromFile("Images/SplashScreen"))
		assert(texture.loadFromFile("Images/SplashScreen.png"));
	sf::Sprite splashLogo(texture);
	GetRenderWindow().draw(splashLogo);

	GetRenderWindow().display();
	sf::Event currentEvent;
	
	// Move to main menu now.
	while (GetRenderWindow().pollEvent(currentEvent))
	{
		if (currentEvent.type == sf::Event::EventType::KeyPressed
			|| currentEvent.type == sf::Event::EventType::MouseButtonPressed
			|| currentEvent.type == sf::Event::EventType::Closed)
		{
			SetGameState(showingMainMenu);
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

	GetRenderWindow().clear(sf::Color(0, 255, 0));
	GetRenderWindow().display();
	sf::Event currentEvent;
	while (GetRenderWindow().pollEvent(currentEvent))
	{
		if (currentEvent.type == sf::Event::EventType::KeyPressed
			|| currentEvent.type == sf::Event::EventType::MouseButtonPressed
			|| currentEvent.type == sf::Event::EventType::Closed)
		{
			SetGameState(playing);
		}
	}
}

void Game::ShowPauseScreen()
{
	GetRenderWindow().clear(sf::Color(0, 255, 255));
	GetRenderWindow().display();
	sf::Event currentEvent;
	while (GetRenderWindow().pollEvent(currentEvent))
	{
		if (currentEvent.type == sf::Event::EventType::KeyPressed
			|| currentEvent.type == sf::Event::EventType::MouseButtonPressed
			|| currentEvent.type == sf::Event::EventType::Closed)
		{
			SetGameState(playing);
		}
	}
}

void Game::ShowGraphicsMenu()
{
	GetRenderWindow().clear(sf::Color(255, 255, 0));
	GetRenderWindow().display();
}

// This handles the actual game logic. What actually happens when the game
// is running. 
void Game::UpdateGame(sf::Event& currentEvent)
{

	if (currentEvent.type == sf::Event::Closed)
		SetGameState(Game::exiting);
	if (currentEvent.key.code == sf::Keyboard::Escape)
		SetGameState(Game::paused);

	GetRenderWindow().clear(sf::Color(255, 0, 0));
	GetRenderWindow().display();

}