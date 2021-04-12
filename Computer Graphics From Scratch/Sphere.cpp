#include "Sphere.h"

#include <corecrt_math.h>

bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
{
	Vec3 originToCenter = ray.origin - center;
	float a = ray.direction.LengthSquared();
	float halfB = originToCenter.Dot(ray.direction);
	float c = originToCenter.LengthSquared() - radius * radius;

	float discriminant = halfB * halfB - a * c;
	if ( discriminant < 0) return false;
	float sqrtD = sqrtf(discriminant);

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
	const Vec3 outwardNormal = (rec.p - center) / radius;
	rec.SetFaceNormal(ray, outwardNormal);
	rec.material = material;

	return true;
}
