#pragma once

#include <cmath>
#include <vector>

#include "Renderer.h"
#include "PhysicsHandler.h"

class Universe
{
public:
	Universe();
	~Universe();

	Universe(sf::RenderWindow* _mainWindow);

	void update(float deltaTime);

	void draw();

	// Adds an object to the universe, if using pixel coords, the function will convert the radius and position
	// to meters. The mass is calculated through density times volume
	Object& spawnObject(bool usingPixelCoords, mymath::Vector2 position, float radius, float density = 10000.0f);

	// Adds kinetic and potential energy to the universe system,
	// Does this by spawning two objects with opposing momentum at the center
	// to maintain a center of mass.
	void addEnergy(float increment, float radius1, float radius2, float angle);

	Object* getObjectAtPos(mymath::Vector2 position);

	Renderer& getRenderer();

private:
	std::vector<Object> objects;
	Renderer renderer;
	PhysicsHandler physicsHandler;
};

