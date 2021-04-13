#pragma once

#include "Hittable.h"

class MovingSphere : public Hittable
{
public:
	MovingSphere() = default;
	MovingSphere(Vec3 centerStart, Vec3 centerEnd, float timeStart, float timeEnd, float radius, std::shared_ptr<Material> material);

	bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override;

	bool BoundingBox(float timeStart, float timeEnd, AABB& outputBox) const override;

	Vec3 Center(float time) const;

public:
	Vec3 center0, center1;
	float time0, time1;
	float radius;
	std::shared_ptr<Material> matPtr;
};

