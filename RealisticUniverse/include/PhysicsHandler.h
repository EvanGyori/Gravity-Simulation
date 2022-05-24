#pragma once

#include <vector>
#include <iostream>

#include "Object.h"
#include "StatisticsTracker.h"

class PhysicsHandler
{
public:
	PhysicsHandler();
	~PhysicsHandler();

	void collisionsUpdate(float deltaTime, std::vector<Object>& objects);

	// Moves the object according to its velocity
	void updatePosition(float deltaTime, Object& object);

	// Moves circles accordingly so they are not intersecting,
	// make sure to calculate distance beforehand and only call
	// if the distance is less then the combined radius and > then 0
	void staticResolution(Object& obj1, Object& obj2, float distance, mymath::Vector2 delta);

	// Transfers velocities between two objects upon impact while conserving momentum
	void dynamicResolution(Object& obj1, Object& obj2, float distance, mymath::Vector2 delta);

	// Uses Newton's gravity formula to attract two objects towards eachother
	void applyGravity(float deltaTime, Object& obj1, Object& obj2, float distance, mymath::Vector2 delta);

private:
	// Most recently calculated distance
	//std::vector<float> distances;
};

