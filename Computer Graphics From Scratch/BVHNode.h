#pragma once
#include "Hittable.h"

class HittableList;

class BVHNode : public Hittable
{
public:
	BVHNode() = default;

	BVHNode(const HittableList& list, float time0, float time1);

	BVHNode(const std::vector<std::shared_ptr<Hittable>>& srcObjects, size_t start, size_t end, float time0, float time1);

	bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override;

	bool BoundingBox(float time0, float time1, AABB& outputBox) const override;

public:
	std::shared_ptr<Hittable> left;
	std::shared_ptr<Hittable> right;
	AABB box;


	static inline bool BoxCompare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, int axis);
	static inline bool BoxXCompare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b);
	static inline bool BoxYCompare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b);
	static inline bool BoxZCompare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b);
};

