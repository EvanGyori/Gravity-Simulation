#include "UserInterface.h"

UserInterface::UserInterface() : universe(nullptr), objectInteract(nullptr)
{
}

UserInterface::~UserInterface()
{
}

UserInterface::UserInterface(Universe* _universe) : universe(_universe), objectInteract(nullptr)
{
}

void UserInterface::mousePressedEvent(bool isMainWindow, sf::Event event)
{
	if (isMainWindow)
	{
		// Keep track of where the mouse button was pressed for
		// use in creating new objects or interacting with objects
		mymath::Vector2 mousePosition(event.mouseButton.x, event.mouseButton.y);
		if (event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right)
		{
			mouseInteractPos = mousePosition;
			mymath::Vector2 mouseWorldPos = universe->getRenderer().convertToMeters(mousePosition);
			Object* object = universe->getObjectAtPos(mouseWorldPos);
			if (object != nullptr)
			{
				objectInteract = object;
				// Use mouseInteractPos for the pivot point
				// instead if moving the object
				if (event.mouseButton.button == sf::Mouse::Left)
					mouseInteractPos = mouseWorldPos - object->position;
			}
		}
	}
}

void UserInterface::mouseReleasedEvent(bool isMainWindow, sf::Event event)
{
	if (isMainWindow)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (objectInteract == nullptr)
				clickAndDragSpawning(event);
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			if (objectInteract != nullptr)
			{
				applyVelocity(event);
			}
		}
	}

	objectInteract = nullptr;
}

void UserInterface::mouseScrolledEvent(bool isMainWindow, sf::Event event)
{
	if (isMainWindow)
	{
		float delta = event.mouseWheelScroll.delta;
		float newCoordsConversion = universe->getRenderer().getCoordsConversion() + universe->getRenderer().getCoordsConversion() * delta * 0.1f; //std::max(1.0f, universe->getRenderer().getCoordsConversion() + delta * zoomSpeed);
		universe->getRenderer().setCoordsConversion(newCoordsConversion);
	}
}

void UserInterface::clickAndDragSpawning(sf::Event event)
{
	if (mouseInteractPos != mymath::Vector2())
	{
		float mouseDistance = mymath::calculateDistance(mouseInteractPos.x, mouseInteractPos.y, event.mouseButton.x, event.mouseButton.y);
		if (mouseDistance > 10)
		{
			universe->spawnObject(true, mouseInteractPos, mouseDistance);
			mouseInteractPos = mymath::Vector2();
		}
	}
}

void UserInterface::applyVelocity(sf::Event event)
{
	Renderer& renderer = universe->getRenderer();
	mymath::Vector2 mouseWorldPos = renderer.convertToMeters(mymath::Vector2(event.mouseButton.x, event.mouseButton.y));
	mymath::Vector2 pivotPoint = renderer.convertToMeters(mouseInteractPos);

	float dx = (pivotPoint.x - mouseWorldPos.x);
	float dy = (pivotPoint.y - mouseWorldPos.y);

	// If the mouse barely moved, remove all velocity, others apply
	if (sqrt(dx * dx + dy * dy) < 0.2f)
	{
		objectInteract->velocity = mymath::Vector2();
	}
	else
	{
		objectInteract->velocity.x += dx;
		objectInteract->velocity.y += dy;
	}
}

void UserInterface::dragObject()
{
	// To move the circle based on the place it was
	// originally grabbed from, set the object's position to
	// the new mouse position minus the pivot/delta position
	Renderer& renderer = universe->getRenderer();
	sf::RenderWindow* mainWindow = renderer.getMainWindow();
	mymath::Vector2 mousePosition(sf::Mouse::getPosition((*mainWindow)).x, sf::Mouse::getPosition((*mainWindow)).y);
	mymath::Vector2 mouseWorldPos = renderer.convertToMeters(mousePosition);

	objectInteract->position.x = mouseWorldPos.x - mouseInteractPos.x;
	objectInteract->position.y = mouseWorldPos.y - mouseInteractPos.y;
}

void UserInterface::movement()
{
	//sf::RenderWindow* mainWindow = universe->getRenderer().getMainWindow();
	mymath::Vector2 vector(0, 0);
	float increment = 0.25f / universe->getRenderer().getCoordsConversion();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		vector.y = -increment;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		vector.y = increment;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		vector.x = -increment;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		vector.x = increment;

	universe->getRenderer().moveCamera(vector);
}

void UserInterface::update()
{
	movement();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && objectInteract != nullptr)
	{
		dragObject();
	}
}

void UserInterface::drawUI()
{
	Renderer& renderer = universe->getRenderer();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseInteractPos != mymath::Vector2() && objectInteract == nullptr)
		renderer.drawDragAndClickSpawning(mouseInteractPos);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mouseInteractPos != mymath::Vector2() && objectInteract != nullptr)
		renderer.drawForceVector(mouseInteractPos);
}