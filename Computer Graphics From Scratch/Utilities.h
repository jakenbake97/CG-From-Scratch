#pragma once
#include <limits>
#include <random>

// Common Headers
#include <chrono>

#include "Ray.h"
#include "Vector.h"
#include "Color.h"

// Constants
constexpr float Pi = 3.1415926535897932385f;
constexpr float Infinity = std::numeric_limits<float>::infinity();

// Utility Functions
inline float DegreesToRadians(float degrees)
{
	return degrees * Pi / 180.0f;
}

inline float RandomValue()
{
	static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	static std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
	return distribution(generator);
}

inline float RandomInRange(float min, float max)
{
	return min + (max - min) * RandomValue();
}

inline int RandomInt(int min, int max)
{
	return static_cast<int>(RandomInRange(min, max + 1));
}

inline Vec3 RandomInUnitSphere()
{
	Vec3 point;
	do
	{
		point = Vec3(RandomInRange(-1, 1), RandomInRange(-1, 1), RandomInRange(-1, 1));
	}
	while (point.LengthSquared() >= 1);

	return point;
}

inline Vec3 RandomUnitVector()
{
	return RandomInUnitSphere().Normalize();
}

inline Vec3 RandomInHemisphere(const Vec3& normal)
{
	const Vec3 inUnitSphere = RandomInUnitSphere();

	if (inUnitSphere.Dot(normal) > 0.0f)
	{
		return inUnitSphere;
	}
	return -inUnitSphere;
}

inline Vec3 RandomInUnitDisk()
{
	Vec3 point;
	do
	{
		point = Vec3(RandomInRange(-1, 1), RandomInRange(-1, 1), 0);
	} 	while (point.LengthSquared() >= 1);

	return point;
}

inline float ClampF(float x, float min, float max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

inline Vec3 Reflect(const Vec3& v, const Vec3& norm)
{
	return v - 2 * v.Dot(norm) * norm;
}

inline Vec3 Refract(const Vec3& uv, const Vec3& n, float etaIOverEtaT)
{
	float cosTheta = fmin(-uv.Dot(n), 1.0f);
	Vec3 rayOutPerp = etaIOverEtaT * (uv + cosTheta * n);
	Vec3 rayOutParallel = -sqrtf(fabs(1.0f - rayOutPerp.LengthSquared())) * n;
	return rayOutPerp + rayOutParallel;
}