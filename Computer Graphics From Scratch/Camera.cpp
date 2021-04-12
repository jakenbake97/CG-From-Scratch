#include "Camera.h"
#include "Ray.h"

Camera::Camera(Vec3 position, Vec3 lookAt, float vFOV, float aspectRatio, float aperture, float focusDist)
	: position(position)
{
	const float theta = DegreesToRadians(vFOV);
	const float h = tan(theta / 2.0f);
	viewportSize.y = 2.0f * h;
	viewportSize.x = aspectRatio * viewportSize.y;

	w = (position - lookAt).Normalize();
	u = Vec3(0, 1, 0).Cross(w).Normalize();
	v = w.Cross(u);

	horizontal = focusDist * viewportSize.x * u;
	vertical = focusDist * viewportSize.y * v;
	lowerLeftCorner = position - horizontal / 2 - vertical / 2 - focusDist * w;

	lensRadius = aperture / 2;
}

Ray Camera::RayThroughViewport(Vec2 pixel) const
{
	Vec3 blurDisk = lensRadius * RandomInUnitDisk();
	Vec3 offset = u * blurDisk.x + v * blurDisk.y;
	return { position + offset, lowerLeftCorner + pixel.u * horizontal + pixel.v * vertical - position - offset };
}
