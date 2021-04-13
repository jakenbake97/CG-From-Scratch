#include "AABB.h"

AABB::AABB(const Vec3& a, const Vec3& b)
{
	minimum = a;
	maximum = b;
}

Vec3 AABB::Min() const
{
	return minimum;
}

Vec3 AABB::Max() const
{
	return maximum;
}

bool AABB::Hit(const Ray& ray, float min, float max) const
{
	for (int axis = 0; axis < 3; axis++)
	{
		const auto inverseDirection = 1.0f / ray.direction[axis];
		auto t0 = (minimum[axis] - ray.origin[axis]) * inverseDirection;
		auto t1 = (maximum[axis] - ray.origin[axis]) * inverseDirection;

		if (inverseDirection < 0.0f)
		{
			std::swap(t0, t1);
		}
		
		min = t0 > min ? t0 : min;
		max = t1 < max ? t1 : max;
		
		if (max <= min)
		{
			return false;
		}
	}

	return true;
}

AABB AABB::SurroundingBox(AABB box0, AABB box1)
{
	const Vec3 small(fmin(box0.minimum.x, box1.minimum.x), fmin(box0.minimum.y, box1.minimum.y), fmin(box0.minimum.z, box1.minimum.z));
	const Vec3 large(fmax(box0.maximum.x, box1.maximum.x), fmax(box0.maximum.y, box1.maximum.y), fmax(box0.maximum.z, box1.maximum.z));
	return {small, large};
}
