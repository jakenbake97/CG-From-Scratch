#include "MovingSphere.h"

#include <utility>

MovingSphere::MovingSphere(Vec3 centerStart, Vec3 centerEnd, float timeStart, float timeEnd, float radius,
                           std::shared_ptr<Material> material)
	: center0(centerStart), center1(centerEnd), time0(timeStart), time1(timeEnd), radius(radius),
	  matPtr(std::move(material))
{
}

bool MovingSphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
{
	const Vec3 originToCenter = ray.origin - Center(ray.time);
	float a = ray.direction.LengthSquared();
	float halfB = originToCenter.Dot(ray.direction);
	float c = originToCenter.LengthSquared() - radius * radius;

	const float discriminant = halfB * halfB - a * c;
	if (discriminant < 0) return false;
	const float sqrtD = sqrtf(discriminant);

	// find the nearest root that lies in the acceptable range
	float root = (-halfB - sqrtD) / a;
	if (root < tMin || tMax < root)
	{
		root = (-halfB + sqrtD) / a;
		if (root < tMin || tMax < root)
			return false;
	}

	rec.t = root;
	rec.p = ray.At(rec.t);
	const Vec3 outwardNormal = (rec.p - Center(ray.time)) / radius;
	rec.SetFaceNormal(ray, outwardNormal);
	rec.material = matPtr;

	return true;
}

bool MovingSphere::BoundingBox(float timeStart, float timeEnd, AABB& outputBox) const
{
	const AABB box0(Center(timeStart) - Vec3(radius), Center(timeEnd) + Vec3(radius));
	const AABB box1(Center(timeEnd) - Vec3(radius), Center(timeEnd) + Vec3(radius));
	outputBox = AABB::SurroundingBox(box0, box1);
	return true;
}

Vec3 MovingSphere::Center(float time) const
{
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}
