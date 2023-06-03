#include "PhysicsHandler.h"

PhysicsHandler::PhysicsHandler()
{
}

PhysicsHandler::~PhysicsHandler()
{
}

void PhysicsHandler::collisionsUpdate(float deltaTime, std::vector<Object>& objects)
{
	// TODO - improve performance
	auto end = std::end(objects);
	for (std::vector<Object>::iterator i = std::begin(objects); i != end; ++i)
	{
		updatePosition(deltaTime, (*i));
		// Interacting with other objects
		for (std::vector<Object>::iterator j = i; j != end; ++j)
		{
			mymath::Vector2 delta(i->position.x - j->position.x, i->position.y - j->position.y);
			float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
			if (distance > 0)
			{
				applyGravity(deltaTime, (*i), (*j), distance, delta);
				if (distance < i->r + j->r)
				{
					staticResolution((*i), (*j), distance, delta);
					dynamicResolution((*i), (*j), distance, delta);
				}
			}
		}
	}
}

void PhysicsHandler::updatePosition(float deltaTime, Object& object)
{
	// TODO - predict and prevent objects from going through other objects at high enough speeds
	object.position.x += object.velocity.x * deltaTime;
	object.position.y += object.velocity.y * deltaTime;
}

void PhysicsHandler::staticResolution(Object& obj1, Object& obj2, float distance, mymath::Vector2 delta)
{
	float overlapDistance = 0.5f * (obj1.r + obj2.r - distance);
	float overlapX = overlapDistance * delta.x / distance;
	float overlapY = overlapDistance * delta.y / distance;

	obj1.position.x += overlapX;
	obj1.position.y += overlapY;
	obj2.position.x -= overlapX;
	obj2.position.y -= overlapY;
}

void PhysicsHandler::dynamicResolution(Object& obj1, Object& obj2, float distance, mymath::Vector2 delta)
{
	// Normal
	float nx = -1.0f * delta.x / distance;
	float ny = -1.0f * delta.y / distance;

	// Tangent
	float tx = -ny;
	float ty = nx;

	// Dot Product Tangent
	float dpTan1 = obj1.velocity.x * tx + obj1.velocity.y * ty;
	float dpTan2 = obj2.velocity.x * tx + obj2.velocity.y * ty;

	// Dot Product Normal
	float dpNorm1 = obj1.velocity.x * nx + obj1.velocity.y * ny;
	float dpNorm2 = obj2.velocity.x * nx + obj2.velocity.y * ny;

	// Conservation of momentum
	float m1 = (dpNorm1 * (obj1.mass - obj2.mass) + 2.0f * obj2.mass * dpNorm2) / (obj1.mass + obj2.mass);
	float m2 = (dpNorm2 * (obj2.mass - obj1.mass) + 2.0f * obj1.mass * dpNorm1) / (obj2.mass + obj1.mass);

	// Update velocities
	obj1.velocity.x = tx * dpTan1 + nx * m1;
	obj1.velocity.y = ty * dpTan1 + ny * m1;
	obj2.velocity.x = tx * dpTan2 + nx * m2;
	obj2.velocity.y = ty * dpTan2 + ny * m2;

	/*
	mymath::Vector2 temp = obj1.velocity;
	obj1.velocity = obj2.velocity;
	obj2.velocity = temp;
	*/
}

void PhysicsHandler::applyGravity(float deltaTime, Object& obj1, Object& obj2, float distance, mymath::Vector2 delta)
{
	// Variables are rearranged for performance reasons, the original equation is accX = (G * M/distance^2) * dx/distance
	float accRatio = deltaTime * gravitationalConstant / pow(distance, 3);
	obj1.velocity.x -= accRatio * delta.x * obj2.mass;
	obj1.velocity.y -= accRatio * delta.y * obj2.mass;
	obj2.velocity.x += accRatio * delta.x * obj1.mass;
	obj2.velocity.y += accRatio * delta.y * obj1.mass;
}