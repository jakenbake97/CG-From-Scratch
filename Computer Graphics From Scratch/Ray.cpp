#include "Ray.h"

Ray::Ray(Vec3 origin, Vec3 direction)
	: origin(origin), direction(direction)
{
}

Vec3 Ray::At(float t) const
{
	return origin + t * direction;
}
