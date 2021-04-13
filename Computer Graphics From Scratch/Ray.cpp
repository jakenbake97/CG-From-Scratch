#include "Ray.h"

Ray::Ray(Vec3 origin, Vec3 direction, float time)
	: origin(origin), direction(direction), time(time)
{
}

Vec3 Ray::At(float t) const
{
	return origin + t * direction;
}
