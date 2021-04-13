#include "BVHNode.h"

#include <iostream>

#include "HittableList.h"

BVHNode::BVHNode(const HittableList& list, float time0, float time1)
	: BVHNode(list.objects, 0, list.objects.size(), time0, time1)
{
}

BVHNode::BVHNode(const std::vector<std::shared_ptr<Hittable>>& srcObjects, size_t start, size_t end, float time0,
	float time1)
{
	auto objects = srcObjects; // modifiable copy of the source objects

	const int axis = RandomInt(0, 2);
	const auto comparator = (axis == 0)
		? BoxXCompare
		: (axis == 1)
		? BoxYCompare
		: BoxZCompare;

	const size_t objectSpan = end - start;
	if (objectSpan == 1)
	{
		left = right = objects[start];
	}
	else if (objectSpan == 2)
	{
		if (comparator(objects[start], objects[start + 1]))
		{
			left = objects[start];
			right = objects[start + 1];
		}
		else
		{
			left = objects[start + 1];
			right = objects[start];
		}
	}
	else
	{
		std::sort(objects.begin() + start, objects.begin() + end, comparator);

		auto mid = start + objectSpan / 2;
		left = std::make_shared<BVHNode>(objects, start, mid, time0, time1);
		right = std::make_shared<BVHNode>(objects, mid, end, time0, time1);
	}

	AABB boxLeft, boxRight;

	if (!left->BoundingBox(time0, time1, boxLeft) || !right->BoundingBox(time0, time1, boxRight))
		std::cerr << "No bounding box in BVHNode constructor!\n";

	box = AABB::SurroundingBox(boxLeft, boxRight);
}

bool BVHNode::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
{
	if (!box.Hit(ray, tMin, tMax)) return false;

	const bool hitLeft = left->Hit(ray, tMin, tMax, rec);
	const bool hitRight = right->Hit(ray, tMin, hitLeft ? rec.t : tMax, rec);

	return hitLeft || hitRight;
}

bool BVHNode::BoundingBox(float time0, float time1, AABB& outputBox) const
{
	outputBox = box;
	return true;
}

bool BVHNode::BoxCompare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, int axis)
{
	AABB boxA;
	AABB boxB;

	if (!a->BoundingBox(0, 0, boxA) || !b->BoundingBox(0, 0, boxB))
		std::cerr << "No bounding box in BVHNode constructor!\n";

	return boxA.Min()[axis] < boxB.Min()[axis];
}

bool BVHNode::BoxXCompare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b)
{
	return BoxCompare(a, b, 0);
}

bool BVHNode::BoxYCompare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b)
{
	return BoxCompare(a, b, 1);
}

bool BVHNode::BoxZCompare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b)
{
	return BoxCompare(a, b, 2);
}


