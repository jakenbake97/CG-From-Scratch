#pragma once
#include "Vector.h"

class Light
{
public:
	enum Type { Ambient, Point, Directional };

	Type type;

	float intensity;

	union
	{
		Vec3 position, direction;
	};

	Light(Type type, float intensity, Vec3 vector = {0, 0, 0})
		: type(type), intensity(intensity), position(vector)
	{
	}
};
