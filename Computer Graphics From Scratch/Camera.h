#pragma once
#include "Color.h"
#include "Vector.h"

class Camera
{
public:
	Camera() = default;
	Camera(Vec3 position, Vec3 lookAt, float vFOV, float aspectRatio, float aperture, float focusDist);
	class Ray RayThroughViewport(Vec2 pixel) const;
	
	Vec3 position;
	Vec2 viewportSize;

private:
	Vec3 lowerLeftCorner;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 u, v, w;
	float lensRadius;
};
