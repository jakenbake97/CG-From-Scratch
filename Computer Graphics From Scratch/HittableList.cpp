#include "HittableList.h"

HittableList::HittableList(std::shared_ptr<Hittable> object)
{
	Add(object);
}

void HittableList::Clear()
{
	objects.clear();
}

void HittableList::Add(std::shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

bool HittableList::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
{
	HitRecord tempRecord;
	bool hitAnything = false;
	float closestSoFar = tMax;

	for (const auto& object : objects)
	{
		if (object->Hit(ray, tMin, closestSoFar, tempRecord))
		{
			hitAnything = true;
			closestSoFar = tempRecord.t;
			rec = tempRecord;
		}
	}

	return hitAnything;
}

bool HittableList::BoundingBox(float time0, float time1, AABB& outputBox) const
{
	if (objects.empty()) return false;

	AABB tempBox;
	bool firstBox = true;

	for (const auto& object : objects)
	{
		if (!object->BoundingBox(time0, time1, tempBox)) return false;
		outputBox = firstBox ? tempBox : AABB::SurroundingBox(outputBox, tempBox);
		firstBox = false;
	}

	return true;
}
