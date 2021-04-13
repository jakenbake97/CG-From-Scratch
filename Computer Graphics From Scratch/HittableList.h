#pragma once
#include "Hittable.h"
#include <memory>
#include <vector>

class HittableList : Hittable
{
public:
	HittableList() = default;
	HittableList(std::shared_ptr<Hittable> object);

	void Clear();
	void Add(std::shared_ptr<Hittable> object);
	bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override;
	bool BoundingBox(float time0, float time1, AABB& outputBox) const override;

public:
	std::vector<std::shared_ptr<Hittable>> objects;
};
