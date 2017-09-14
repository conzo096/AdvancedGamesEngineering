#include "Game.h"
#include "stdafx.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "PlayerShip.h"
#include "SFMLSoundProvider.h"
#include "ServiceLocator.h"
#include "GraphicsMenu.h"
#include "PauseScreen.h"
#include "GameOverScreen.h"
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
	GetRenderWindow().create(sf::VideoMode(GetScreenWidth(), GetScreenHeight(), 32), "Week One Project!", sf::Style::Default);
	SetView(sf::View(sf::FloatRect(0, 0, GetScreenWidth(),GetScreenHeight())));


	//Load in all the characters.
	PlayerShip *player = new PlayerShip();
	player->GetSprite().setPosition(screenWidth/2,screenHeight/2);
	GetGameManager().AddObject("Player", player);
	// Change the game state to display the splash logo.
	SetGameState(showingSplashScreen);
	GameLoop();
}

void Game::ResetGame()
{
	GetGameManager().DeleteAll();

	// Reset score,wave and time.
	GetGameManager().score = 0;
	GetGameManager().wave = 0;
	// Allow new wave to be spawned.
	GetGameManager().createNewWave = true;

	//Load in all the characters.
	PlayerShip *player = new PlayerShip();
	player->GetSprite().setPosition(screenWidth / 2, screenHeight / 2);
	GetGameManager().AddObject("Player", player);
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
				UpdateGame();
				break;
			}
			case gameOver:
			{
				ShowGameOver();
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
		case::MainMenu::showGraphicsOption:
		{
			SetGameState(Game::showingGraphicsMenu);
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
	PauseMenu options;
	PauseMenu::MenuResult result = options.Show(mainWindow);
	switch (result)
	{
		case::PauseMenu::nothing:
		{
			SetGameState(Game::paused);
			break;
		}
		case PauseMenu::keepPlaying:
		{
			SetGameState(Game::playing);
			Game::GetClock().restart();
			break;
		}
		case PauseMenu::showMainMenu:
		{
			SetGameState(Game::showingMainMenu);
			ResetGame();
			break;
		}

	}
}


void Game::ShowGraphicsMenu()
{
	GraphicsOption options;
	GraphicsOption::MenuResult result = options.Show(mainWindow);
	switch (result)
	{
		case::GraphicsOption::nothing:
		{
			SetGameState(Game::showingGraphicsMenu);
			break;
		}
		case GraphicsOption::exitMenu:
		{
			SetGameState(Game::showingMainMenu);
			break;
		}
	}
}

void Game::ShowGameOver()
{
	GameOverScreen options;
	GameOverScreen::MenuResult result = options.Show(mainWindow);
	switch (result)
	{
		case::GameOverScreen::nothing:
		{
			SetGameState(Game::gameOver);
			break;
		}
		case::GameOverScreen::showMainMenu:
		{
			SetGameState(Game::showingMainMenu);
			break;
		}
		case::GameOverScreen::exit:
		{
			SetGameState(Game::exiting);
			break;
		}
	}
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
		font.loadFromFile("res/Fonts/Cracked Code.ttf");
		sf::Text myText;
		// Assign the actual message 
		PlayerShip* pl = (PlayerShip*)gameManager.Get("Player");
		if (pl != NULL)
		{
			myText.setString(std::to_string(pl->GetHealth()));
		}
		else
		{
			myText.setString("WHERE DID THE SHIP GO?");
			AddScore(GetGameManager().score);
			std::sort(highScores.begin(), highScores.end(), GameManager::GreaterScore());
			Game::SetGameState(Game::gameOver);
			//ResetGame();
		}
		// assign a size 
		myText.setCharacterSize(20);

		// Choose a color 
		myText.setFillColor(sf::Color::Blue);
		myText.setOrigin(myText.getString().getSize() / 2, myText.getScale().y / 2);
		myText.setPosition(Game::GetScreenWidth()*0.02, Game::GetScreenHeight()*0.02);

		// Set the font to our Text object 
		myText.setFont(font);

		sf::Text wave;

		wave.setString(std::to_string(Game::GetGameManager().wave));
		wave.setCharacterSize(20);

		// Choose a color 
		wave.setFillColor(sf::Color::Blue);
		wave.setOrigin(myText.getString().getSize() / 2, myText.getScale().y / 2);
		wave.setPosition(Game::GetScreenWidth()*0.9, Game::GetScreenHeight()*0.02);

		// Set the font to our Text object 
		wave.setFont(font);	

		sf::Text score;
		score.setString(std::to_string(Game::GetGameManager().score));
		score.setCharacterSize(20);

		// Choose a color 
		score.setFillColor(sf::Color::Blue);
		score.setOrigin(myText.getString().getSize() / 2, myText.getScale().y / 2);
		score.setPosition(Game::GetScreenWidth()*0.9, Game::GetScreenHeight()*0.05);

		// Set the font to our Text object 
		score.setFont(font);

		if (currentEvent.key.code == sf::Keyboard::Escape || sf::Joystick::isButtonPressed(0, sf::Joystick::PovY))
		{
			SetGameState(Game::paused);
			GetGameManager().StopSounds();
			return;
		}
		
		GetRenderWindow().clear(sf::Color(255, 255, 255));

		gameManager.UpdateAll(physicsClock.restart().asSeconds());


		gameManager.DrawAll(GetRenderWindow());
		GetRenderWindow().draw(myText);
		GetRenderWindow().draw(wave);
		GetRenderWindow().draw(score);
		if (gameManager.enemiesAlive == 0)
			gameManager.createNewWave = true;

		GetRenderWindow().display();
	}
}