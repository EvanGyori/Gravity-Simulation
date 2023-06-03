#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.h"

// The object in this case will be a circle
// position and velocity is in meters
// mass is in kilograms
struct Object
{
	sf::CircleShape circle;
	mymath::Vector2 position, velocity;
	float r, mass;

	Object(mymath::Vector2 _position, float _radius, float _mass, mymath::Vector2 _velocity = mymath::Vector2(0, 0))
	{
		position = _position;
		r = _radius;
		mass = _mass;
		velocity = _velocity;
		mass = r * r * 3;
		circle = sf::CircleShape(r);
	}
};