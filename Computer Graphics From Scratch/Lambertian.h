#pragma once
#include "Material.h"
class Lambertian : public Material
{
public:
	Lambertian(Color color) : albedo(color) {}
	
	bool Scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

	Color albedo;
};

