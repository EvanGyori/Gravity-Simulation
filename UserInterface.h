#pragma once

#include <SFML/Window.hpp>
#include <cmath>

#include "Universe.h"

class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	UserInterface(Universe* _universe);

	void mousePressedEvent(bool isMainWindow, sf::Event event);

	void mouseReleasedEvent(bool isMainWindow, sf::Event event);

	void mouseScrolledEvent(bool isMainWindow, sf::Event event);

	// Left click on a spot and drag to determine the radius
	// of the object to be spawned
	void clickAndDragSpawning(sf::Event event);

	// Hold right click on object and let go to apply
	// velocity in a direction
	void applyVelocity(sf::Event event);

	// Move the targeted object along with the mouse
	// relative to the pivot point
	void dragObject();

	void movement();

	void update();

	void drawUI();

private:
	const float zoomSpeed = 5.0f;

	Universe* universe;
	mymath::Vector2 mouseInteractPos;
	// Keep track of a object for moving and giving impulse
	Object* objectInteract;
};

