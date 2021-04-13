#include "Metal.h"

#include "Hittable.h"

bool Metal::Scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
	Vec3 inputRay = rayIn.direction;
	const Vec3 reflected = Reflect(inputRay.Normalize(), rec.normal);
	scattered = Ray(rec.p, reflected + roughness * RandomInUnitSphere(), rayIn.time);
	attenuation = albedo;
	return scattered.direction.Dot(rec.normal) > 0;
}
