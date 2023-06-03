#pragma once

#include "mymath.h"

namespace mymath
{
	struct Vector2
	{
		float x, y;

		Vector2()
		{
			x = 0;
			y = 0;
		}

		Vector2(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

		static float getDistance(Vector2 pos1, Vector2 pos2)
		{
			return calculateDistance(pos1.x, pos1.y, pos2.x, pos2.y);
		}

		bool operator==(Vector2 right)
		{
			return (x == right.x && y == right.y);
		}

		bool operator!=(Vector2 right)
		{
			return (x != right.x || y != right.y);
		}

		Vector2 operator-(Vector2 right)
		{
			return Vector2(x - right.x, y - right.y);
		}
	};
}