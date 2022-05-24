#pragma once

#include <cmath>

#include "Object.h"

extern const double gravitationalConstant;

class StatisticsTracker
{
public:
	StatisticsTracker();
	~StatisticsTracker();

	// Calculates the gravitational potential energy between two objects,
	// returns a negative number due to the nature of the formula
	static float calculateGPE(float distance, float mass1, float mass2);

	static float calculateKineticEnergy(Object object);
};

