#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Object.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	Renderer(sf::RenderWindow* _mainWindow);

	// Input pixel coordinates from the main window
	// and will output meter coordinates in the context of the universe
	mymath::Vector2 convertToMeters(mymath::Vector2 pixels);

	// Input meter coordinates in the context of the universe
	// and will output pixel coordinates for the main window
	mymath::Vector2 convertToPixels(mymath::Vector2 meters);

	// set pixelsToMeters
	void setCoordsConversion(float value);

	// Returns pixelsToMeters
	float getCoordsConversion();

	sf::RenderWindow* getMainWindow();

	void drawUniverse(std::vector<Object>& objects);

	// Draw the clickAndDragSpawning feature
	// by drawing an outline of the circle that
	// is about to be created
	void drawDragAndClickSpawning(mymath::Vector2 position);

	// Draw the line when right clicking and
	// dragging to apply velocity to an object
	void drawForceVector(mymath::Vector2 position);

	// Clears anything drawn to the window,
	// call before any drawing functions
	void clearWindows();

	// Displays anything drawn to the window
	// call after every drawing function
	void displayWindows();

	void moveCamera(mymath::Vector2 vector);

private:
	sf::RenderWindow* mainWindow;
	//sf::RenderWindow* statisticsWindow;
	float pixelsToMeter;
	// The camera position is in meters
	mymath::Vector2 cameraPosition;
};

