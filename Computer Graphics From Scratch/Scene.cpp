#include "Scene.h"

#include <utility>

Scene::Scene() = default;

Scene::Scene(const Camera cam)
	: camera(cam)
{
}

void Scene::AddObjectToScene(Sphere newSphere)
{
	objects.push_back(newSphere);
}

void Scene::AddLightToScene(Light light)
{
	lights.push_back(light);
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

	const auto a = direction.Dot(direction);
	const auto b = 2 * sphereToOrigin.Dot(direction);
	const auto c = sphereToOrigin.Dot(sphereToOrigin) - sphere.radius * sphere.radius;

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
	float closestDistance = std::numeric_limits<float>::infinity();
	Sphere* closestSphere = nullptr;

	for (auto& sphere : objects)
	{
		const Vec2 hitPoints = RaySphereIntersection(camera.position, rayDirection, sphere);

		if (hitPoints.x < closestDistance && (minDist < hitPoints.x && hitPoints.x < maxDist))
		{
			closestDistance = hitPoints.x;
			closestSphere = &sphere;
		}
		if (hitPoints.y < closestDistance && (minDist < hitPoints.y && hitPoints.y < maxDist))
		{
			closestDistance = hitPoints.y;
			closestSphere = &sphere;
		}
	}

	if (closestSphere == nullptr)
	{
		return camera.clearColor;
	}

	auto point = camera.position + rayDirection * closestDistance;
	auto norm = point - closestSphere->center;
	norm.Normalize();

	return closestSphere->color * ComputeLighting(point, norm, rayDirection * -1.0f, closestSphere->specular);
}

float Scene::ComputeLighting(Vec3 point, Vec3 normal, Vec3 view, int specular)
{
	float intensity = 0.0f;
	const float normalLength = normal.Length();
	float viewLength = view.Length();

	for (auto& light : lights)
	{
		if (light.type == Light::Ambient)
		{
			intensity += light.intensity;
		}
		else
		{
			Vec3 lightVector;
			if (light.type == Light::Point)
			{
				lightVector = light.position - point;
			}
			else
			{
				lightVector = light.direction;
			}

			// Diffuse reflection
			const float normDotLight = normal.Dot(lightVector);

			if (normDotLight > 0)
			{
				intensity += light.intensity * normDotLight / (normalLength * lightVector.Length());
			}

			// Specular Reflection
			if (specular >= 0)
			{
				float scaledDot = 2.0f * normal.Dot(lightVector);
				Vec3 reflectionVector = (normal * scaledDot) - lightVector;
				const float reflectionDotView = reflectionVector.Dot(view);
				if (reflectionDotView > 0)
				{
					intensity += light.intensity * powf(reflectionDotView / (reflectionVector.Length() * viewLength),
					                                    specular);
				}
			}
		}
	}

	return intensity;
}
