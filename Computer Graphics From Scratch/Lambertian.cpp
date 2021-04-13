#include "Lambertian.h"

#include "Hittable.h"

bool Lambertian::Scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
	Vec3 scatterDirection = rec.normal + RandomUnitVector();

	if (scatterDirection.NearZero())
	{
		scatterDirection = rec.normal;
	}
	
	scattered = Ray(rec.p, scatterDirection, rayIn.time);
	attenuation = albedo;
	return true;
}
