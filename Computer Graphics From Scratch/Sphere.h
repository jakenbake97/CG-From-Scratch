#pragma once
#include "Color.h"
#include "Vector.h"

class Sphere
{
public:
	Sphere(Vec3 center, float radius, Color color, int specular)
		: center(center), radius(radius), color(color), specular(specular)
	{
	}

	Sphere()
		: center({0,0,0}), radius(0), color({0,0,0,0})
	{}

	Vec3 center;
	float radius;
	Color color;
	int specular;
};
