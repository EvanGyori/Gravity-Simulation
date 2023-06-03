#include <SFML/Graphics.hpp>
#include <iostream>

#include "Universe.h"
#include "UserInterface.h"

int main()
{
	// deltaTime is in seconds
	float deltaTime = 0.0f;
	sf::RenderWindow mainWindow(sf::VideoMode(800, 800), "The Universe");
	//sf::RenderWindow statisticsWindow();
	Universe universe(&mainWindow);
	UserInterface userInterface(&universe);

	/*
	for (int i = 0; i < 50; i++)
	{
		universe.spawnObject(false, mymath::Vector2(0, 0), 1);
		universe.spawnObject(false, mymath::Vector2(0.5, 0), 1);
		universe.spawnObject(false, mymath::Vector2(0, 0.5), 1);
		universe.spawnObject(false, mymath::Vector2(0.5, 0.5), 1);
	}
	*/

	sf::Clock deltaClock;
	while (mainWindow.isOpen())
	{
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					mainWindow.close();
					break;
				case sf::Event::MouseButtonPressed:
					userInterface.mousePressedEvent(true, event);
					break;
				case sf::Event::MouseButtonReleased:
					userInterface.mouseReleasedEvent(true, event);
					break;
				case sf::Event::MouseWheelScrolled:
					userInterface.mouseScrolledEvent(true, event);
					break;
				case sf::Event::Resized:
					sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
					mainWindow.setView(sf::View(visibleArea));
					break;
			}

			//else if (event.type == sf::Event::Resized)
			//	mainWindow.setSize(sf::Vector2u(event.size.width, event.size.height));
			//(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			//(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		}

		universe.update(deltaTime);
		userInterface.update();

		universe.getRenderer().clearWindows();

		universe.draw();
		userInterface.drawUI();

		universe.getRenderer().displayWindows();

		deltaTime = deltaClock.restart().asSeconds();
	}

	return 0;
}