#pragma once
#include "Color.h"
#include "Vector.h"

struct Sphere
{
public:
	Vec3 center;
	float radius;
	Color color{0,0,0,0};
	int specular;
	float reflectivity;
};
