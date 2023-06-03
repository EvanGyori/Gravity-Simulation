#include "Universe.h"

Universe::Universe()
{
}

Universe::~Universe()
{
}

Universe::Universe(sf::RenderWindow* _mainWindow) : renderer(Renderer(_mainWindow))
{
}

void Universe::update(float deltaTime)
{
	physicsHandler.collisionsUpdate(deltaTime, objects);
}

void Universe::draw()
{
	renderer.drawUniverse(objects);
}

Object& Universe::spawnObject(bool usingPixelCoords, mymath::Vector2 position, float radius, float density)
{
	// Translate position and radius to universe scale
	if (usingPixelCoords)
	{
		position = renderer.convertToMeters(position);
		radius /= renderer.getCoordsConversion();
	}

	// mass formula is density * volume
	float mass = density * radius * radius * 3.142;
	Object object(position, radius, mass);
	objects.push_back(object);

	return object;
}

void Universe::addEnergy(float increment, float radius1, float radius2, float angle)
{
	// TODO - include GPE as part of the increment if possible (currently adds an unknown amount of GPE but an exact kinetic energy)
	// TODO - Finish
	float mass1 = radius1 * radius1 * 3;
	float velocity1 = sqrt(increment / mass1);

	float mass2 = radius2 * radius2 * 3;
	float velocity2 = sqrt(increment / mass2);
}

Object* Universe::getObjectAtPos(mymath::Vector2 position)
{
	for (auto& object : objects)
	{
		float distance = mymath::Vector2::getDistance(position, object.position);
		if (distance <= object.r)
		{
			return &object;
		}
	}

	return nullptr;
}

Renderer& Universe::getRenderer()
{
	return renderer;
}