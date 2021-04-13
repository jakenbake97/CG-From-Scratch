#pragma once
#include "Utilities.h"

class AABB
{
public:
	AABB() = default;
	AABB(const Vec3& a, const Vec3& b);

	Vec3 Min() const;
	Vec3 Max() const;

	bool Hit(const Ray& ray, float min, float max) const;
	static AABB SurroundingBox(AABB box0, AABB box1);

private:
	Vec3 minimum;
	Vec3 maximum;
};

