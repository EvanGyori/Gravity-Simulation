#include "Renderer.h"

Renderer::Renderer() : mainWindow(nullptr)
{
	pixelsToMeter = 100;
}

Renderer::~Renderer()
{
}

Renderer::Renderer(sf::RenderWindow* _mainWindow) : mainWindow(_mainWindow)
{
	pixelsToMeter = 100;
}

mymath::Vector2 Renderer::convertToMeters(mymath::Vector2 pixels)
{
	mymath::Vector2 meters(0, 0);
	meters.x = (pixels.x - mainWindow->getSize().x / 2.0f) / pixelsToMeter + cameraPosition.x;
	meters.y = (pixels.y - mainWindow->getSize().y / 2.0f) / pixelsToMeter + cameraPosition.y;

	return meters;
}

mymath::Vector2 Renderer::convertToPixels(mymath::Vector2 meters)
{
	mymath::Vector2 pixels(0, 0);
	pixels.x = pixelsToMeter * (meters.x - cameraPosition.x) + mainWindow->getSize().x / 2.0f;
	pixels.y = pixelsToMeter * (meters.y - cameraPosition.y) + mainWindow->getSize().y / 2.0f;

	return pixels;
}

void Renderer::setCoordsConversion(float value)
{
	pixelsToMeter = value;
}

float Renderer::getCoordsConversion()
{
	return pixelsToMeter;
}

sf::RenderWindow* Renderer::getMainWindow()
{
	return mainWindow;
}

void Renderer::drawUniverse(std::vector<Object>& objects)
{
	for (auto& object : objects)
	{
		mymath::Vector2 pixelPosition = convertToPixels(object.position);
		float pixelRadius = object.r * pixelsToMeter;
		object.circle.setRadius(pixelRadius);
		object.circle.setPosition(pixelPosition.x - pixelRadius, pixelPosition.y - pixelRadius);
		mainWindow->draw(object.circle);
	}
}

void Renderer::drawDragAndClickSpawning(mymath::Vector2 position)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition((*mainWindow));
	float radius = mymath::calculateDistance(position.x, position.y, mousePosition.x, mousePosition.y);
	if (radius > 10)
	{
		sf::CircleShape outlineCircle(radius);
		outlineCircle.setPosition(position.x - radius, position.y - radius);
		outlineCircle.setFillColor(sf::Color::Transparent);
		outlineCircle.setOutlineColor(sf::Color(255, 157, 0));
		outlineCircle.setOutlineThickness(1);
		mainWindow->draw(outlineCircle);
	}
}

void Renderer::drawForceVector(mymath::Vector2 position)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition((*mainWindow));
	sf::Vertex line[2];
	line[0].position = sf::Vector2f(position.x, position.y);
	line[0].color = sf::Color::Green;
	line[1].position = sf::Vector2f(mousePosition.x, mousePosition.y);
	line[1].color = sf::Color::Green;

	mainWindow->draw(line, 2, sf::Lines);
}

void Renderer::clearWindows()
{
	mainWindow->clear();
}

void Renderer::displayWindows()
{
	mainWindow->display();
}

void Renderer::moveCamera(mymath::Vector2 vector)
{
	cameraPosition.x += vector.x;
	cameraPosition.y += vector.y;
}
