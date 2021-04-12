#pragma once
#include "Material.h"
class Dielectric : public Material
{
public:
	Dielectric(float indexOfRefraction) : ir(indexOfRefraction) {};
	bool Scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

	float ir;
private:
	static float Reflectance(float cosine, float refIdx);
};

