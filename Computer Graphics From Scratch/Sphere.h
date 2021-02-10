#pragma once
#include "Color.h"
#include "Vector.h"

class Sphere
{
public:
	Sphere(Vec3 center, float radius, Color color)
		: center(center), radius(radius), color(color)
	{
	}

	Sphere()
		: center({0,0,0}), radius(0), color({0,0,0,0})
	{}

	Vec3 center;
	float radius;
	Color color;
};
