#include "Game.h"
#include "stdafx.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "PlayerShip.h"
Game *Game::instance = 0;


Game::Game() : screenWidth(1920), screenHeight(1080), gameState(uninitialized), clock(sf::Clock())
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
	//Load in all the characters.
	PlayerShip *player = new PlayerShip();
	player->LoadSprite("Images/GameObjects/PlayerShip.png");
	player->GetSprite().setOrigin(sf::Vector2f(float(player->GetSprite().getTexture()->getSize().x) / 2, float(player->GetSprite().getTexture()->getSize().y) / 2));
	player->GetSprite().setPosition(screenWidth/2,screenHeight/2);
	GetGameManager().AddObject("Player", player);
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
				Instance()->UpdateGame();
				break;
			}
		}
	}
}

// Displays the splash screen state.
void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(GetRenderWindow());
	SetGameState(showingMainMenu);
}


// Display the main menu screen.
void Game::ShowMainMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(mainWindow);
	switch (result)
	{
		case MainMenu::playGame:
		{
			SetGameState(Game::playing);
			break;
		}
		case MainMenu::exitApplication:
		{
			SetGameState(Game::exiting);
			break;
		}
	}
}

void Game::ShowPauseScreen()
{

	Instance()->ShowMainMenu();
	/*GetRenderWindow().clear(sf::Color(0, 255, 255));
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
	}*/
}

//Not yet implemented.
void Game::ShowGraphicsMenu()
{
	GetRenderWindow().clear(sf::Color(255, 255, 0));
	GetRenderWindow().display();
}

// This handles the actual game logic. What actually happens when the game
// is running. 
void Game::UpdateGame()
{
	sf::Event currentEvent;
	sf::Clock physicsClock;
	while (GetGameState() == playing)
	{
		if (gameManager.createNewWave == true)
		{
			gameManager.SpawnWave(mainWindow);
			gameManager.createNewWave = false;
		}
		mainWindow.pollEvent(currentEvent);
		sf::Font font;
		font.loadFromFile("Fonts/Cracked Code.ttf");
		sf::Text myText;
		// Assign the actual message 
		PlayerShip* pl = (PlayerShip*)gameManager.Get("Player");
		if (pl != NULL)
		{
			myText.setString(std::to_string(pl->GetHealth()));
		}
		else
		{
			myText.setString("Where did the ship go?");
		}
		// assign a size 
		myText.setCharacterSize(15);

		// Choose a color 
		myText.setFillColor(sf::Color::White);

		// Set the font to our Text object 
		myText.setFont(font);

		if (currentEvent.type == sf::Event::Closed)
			SetGameState(Game::exiting);
		if (currentEvent.key.code == sf::Keyboard::Escape)
			SetGameState(Game::paused);

		GetRenderWindow().clear(sf::Color(255, 255, 255));

	

		gameManager.UpdateAll(physicsClock.restart().asSeconds());


		gameManager.DrawAll(GetRenderWindow());
		GetRenderWindow().draw(myText);
		if (gameManager.enemiesAlive == 0)
			gameManager.createNewWave = true;

		GetRenderWindow().display();
	}
}