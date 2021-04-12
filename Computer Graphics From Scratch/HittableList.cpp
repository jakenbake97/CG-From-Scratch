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
