#include "Dielectric.h"

#include "Hittable.h"

bool Dielectric::Scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
	attenuation = Color(1.0f, 1.0f, 1.0f);
	const float refractionRatio = rec.frontFace ? (1.0f / ir) : ir;

	Vec3 unitDirection = Vec3(rayIn.direction).Normalize();
	float cosTheta = fmin(-unitDirection.Dot(rec.normal), 1.0f);
	float sinTheta = sqrtf(1.0f - cosTheta * cosTheta);

	Vec3 direction;
	if (refractionRatio * sinTheta > 1.0f || Reflectance(cosTheta, refractionRatio) > RandomValue())
	{
		direction = Reflect(unitDirection, rec.normal);
	}
	else
	{
		direction = Refract(unitDirection, rec.normal, refractionRatio);
	}
	
	scattered = Ray(rec.p, direction);
	return true;
}

float Dielectric::Reflectance(float cosine, float refIdx)
{
	// Schlick's approximation for reflectance
	float r0 = (1 - refIdx) / (1 + refIdx);
	r0 *= r0;
	return r0 = (1 - r0) * pow((1 - cosine), 5);
}
