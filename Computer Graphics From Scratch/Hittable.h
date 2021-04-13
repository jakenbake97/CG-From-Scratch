#pragma once
#include <memory>

#include "AABB.h"
#include "Ray.h"

class Material;

struct HitRecord
{
	Vec3 p;
	Vec3 normal;
	std::shared_ptr<Material> material;
	float t;
	bool frontFace;

	void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal)
	{
		frontFace = ray.direction.Dot(outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable
{
public:
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const = 0;
	virtual bool BoundingBox(float time0, float time1, AABB& outputBox)const = 0;
};
