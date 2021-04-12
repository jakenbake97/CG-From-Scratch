#pragma once
#include "Vector.h"

class Ray
{
public:
	Ray() = default;
	Ray(Vec3 origin, Vec3 direction);

	Vec3 At(float t) const;
	
	Vec3 origin;
	Vec3 direction;
};
