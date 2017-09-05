#include "SplashScreen.h"


SplashScreen::SplashScreen()
{
}


SplashScreen::~SplashScreen()
{
}

void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	// Time until splash screen is over.
	float timeRemaining =3.0;
	sf::Clock timer;
	sf::Texture image;
	if (image.loadFromFile("Images/SplashScreen.png") != true)
	{
		return;
	}
	sf::Sprite sprite(image);
	renderWindow.clear();
	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (true)
	{

		renderWindow.pollEvent(event);
		if (event.type == sf::Event::EventType::KeyPressed
			||timer.getElapsedTime().asSeconds() >= timeRemaining)
		{
			return;
		}
	}
}