#include "GraphicsMenu.h"
#include "Game.h"


GraphicsOption::GraphicsOption()
{
}


GraphicsOption::~GraphicsOption()
{
}

void GraphicsOption::Show(sf::RenderWindow & renderWindow)
{
	sf::Font font;
	font.loadFromFile("Fonts/Cracked Code.ttf");
	//Load menu image from file
	sf::Texture image;
	image.loadFromFile("images/GraphicsMenu.png");
	sf::Sprite sprite(image);
	sprite.setScale(sf::Vector2f(float(image.getSize().x) / Game::Instance()->GetScreenWidth(), float(image.getSize().y) / Game::Instance()->GetScreenHeight()));
	//Setup clickable regions
	sf::Text defaultRes;
	defaultRes.setFont(font);
	defaultRes.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, Game::Instance()->Game::GetScreenHeight() / 3);
	/*sf::Text defaultRes1;
	defaultRes1.setFont(font);
	defaultRes.setFont(font);
	defaultRes.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, Game::Instance()->Game::GetScreenHeight() / 3);
	sf::Text defaultRes2;
	defaultRes2.setFont(font);
	defaultRes.setFont(font);
	defaultRes.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, Game::Instance()->Game::GetScreenHeight() / 3);*/
	sf::Text fullScreen;
	fullScreen.setFont(font);
	defaultRes.setFont(font);
	defaultRes.setPosition(Game::Instance()->Game::GetScreenWidth() / 2, Game::Instance()->Game::GetScreenHeight() / 3);

	renderWindow.draw(sprite);
	renderWindow.draw(defaultRes);
//	renderWindow.draw(defaultRes1);
//	renderWindow.draw(defaultRes2);
	renderWindow.draw(fullScreen);

	renderWindow.display();


	while (true)
	{
		sf::Event event;
		renderWindow.pollEvent(event);
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (defaultRes.getGlobalBounds().contains(Game::Instance()->GetRenderWindow().mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
			{
				
			}

		}
	}
}


