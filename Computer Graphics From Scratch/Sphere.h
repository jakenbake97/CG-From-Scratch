#pragma once
#include <utility>

#include "Hittable.h"
#include "Color.h"
#include "Vector.h"

class Sphere : public Hittable
{
public:
	Sphere() = default;

	Sphere(Vec3 center, float radius, std::shared_ptr<Material> material)
		: center(center), radius(radius), material(std::move(material))
	{
	}

	bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override;

	bool BoundingBox(float time0, float time1, AABB& outputBox) const override;

public:
	Vec3 center;
	float radius;
	std::shared_ptr<Material> material;
};
