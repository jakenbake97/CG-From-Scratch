#include "Scene.h"

#include <utility>

Scene::Scene() = default;

Scene::Scene(Camera cam)
	: camera(std::move(cam))
{
}

void Scene::AddObjectToScene(Sphere newSphere)
{
	objects.push_back(newSphere);
}

void Scene::CreateCamera(Vec3 position, Vec2 viewport, float nearPlane, Color clearColor)
{
	camera.position = position;
	camera.viewportSize = viewport;
	camera.projectionPlaneDistance = nearPlane;
	camera.clearColor = clearColor;
}

Vec2 Scene::RaySphereIntersection(const Vec3& origin, const Vec3& direction, const Sphere& sphere)
{
	auto sphereToOrigin = origin - sphere.center;

	const auto a = Vec3::DotProduct(direction, direction);
	const auto b = 2 * Vec3::DotProduct(sphereToOrigin, direction);
	const auto c = Vec3::DotProduct(sphereToOrigin, sphereToOrigin) - sphere.radius * sphere.radius;

	const auto discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return {std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()};
	}

	Vec2 hitPoints;
	hitPoints.x = (-b + (float)sqrt(discriminant)) / (2.0f * a);
	hitPoints.y = (-b + (float)sqrt(discriminant)) / (2.0f * a);
	return hitPoints;
}

Color Scene::TraceRay(Vec3 rayDirection, float minDist, float maxDist)
{
	float closestPoint = std::numeric_limits<float>::infinity();
	Sphere* closestSphere = nullptr;

	for (auto& sphere : objects)
	{
		const Vec2 hitPoints = RaySphereIntersection(camera.position, rayDirection, sphere);

		if (hitPoints.x < closestPoint && (minDist < hitPoints.x && hitPoints.x < maxDist))
		{
			closestPoint = hitPoints.x;
			closestSphere = &sphere;
		}
		if (hitPoints.y < closestPoint && (minDist < hitPoints.y && hitPoints.y < maxDist))
		{
			closestPoint = hitPoints.y;
			closestSphere = &sphere;
		}
	}

	if (closestSphere == nullptr)
	{
		return camera.clearColor;
	}

	return closestSphere->color;
}
