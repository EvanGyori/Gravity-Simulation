#include "StatisticsTracker.h"

const double gravitationalConstant = 6.6743 * pow(10, -1);

StatisticsTracker::StatisticsTracker()
{
}

StatisticsTracker::~StatisticsTracker()
{
}

float StatisticsTracker::calculateGPE(float distance, float mass1, float mass2)
{
	return -gravitationalConstant * mass1 * mass2 / distance;
}

float StatisticsTracker::calculateKineticEnergy(Object object)
{
	return 0.5f * object.mass * (object.velocity.x * object.velocity.x + object.velocity.y * object.velocity.y);
}
