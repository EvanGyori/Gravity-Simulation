#include "mymath.h"

float mymath::calculateDistance(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	return sqrt(dx * dx + dy * dy);
}

float mymath::lerpValue(float a, float b, float x)
{
	return a + (b - a) * x;
}