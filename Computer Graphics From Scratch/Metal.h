#pragma once
#include "Material.h"
class Metal : public Material
{
public:
	Metal(Color color, float roughness) : albedo(color), roughness(roughness) {}
	bool Scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

	Color albedo;
	float roughness;
};

