#include "Scene.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

Scene::Scene() = default;

Scene::Scene(const Camera cam)
	: camera(cam)
{
}

void Scene::AddObjectToScene(Sphere* pNewSphere)
{
	objects.push_back(pNewSphere);
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

Vec2 Scene::RaySphereIntersection(const Vec3& origin, const Vec3& direction, const Sphere* sphere)
{
	const auto sphereToOrigin = origin - sphere->center;

	const auto a = direction.Dot(direction);
	const auto b = 2 * sphereToOrigin.Dot(direction);
	const auto c = sphereToOrigin.Dot(sphereToOrigin) - sphere->radius * sphere->radius;

	const auto discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return {std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()};
	}

	Vec2 hitPoints;
	hitPoints.x = (-b + sqrtf(discriminant)) / (2.0f * a);
	hitPoints.y = (-b - sqrtf(discriminant)) / (2.0f * a);
	return hitPoints;
}


void Scene::ClosestIntersection(Vec3 origin, Vec3 rayDirection, float minDist, float maxDist, float& closestDistance,
                                Sphere** closestSphere)
{
	closestDistance = std::numeric_limits<float>::infinity();
	*closestSphere = nullptr;

	for (auto* sphere : objects)
	{
		const Vec2 hitPoints = RaySphereIntersection(origin, rayDirection, sphere);

		if (hitPoints.x < closestDistance && (minDist < hitPoints.x && hitPoints.x < maxDist))
		{
			closestDistance = hitPoints.x;
			*closestSphere = sphere;
		}
		if (hitPoints.y < closestDistance && (minDist < hitPoints.y && hitPoints.y < maxDist))
		{
			closestDistance = hitPoints.y;
			*closestSphere = sphere;
		}
	}
}

Vec3 Scene::ReflectRay(Vec3 ray, Vec3 normal)
{
	return normal * normal.Dot(ray) * 2 - ray;
}

Color Scene::TraceRay(Vec3 origin, Vec3 rayDirection, float minDist, float maxDist, uint32_t recursionDepth)
{
	float closestDistance;
	Sphere* closestSphere{};
	ClosestIntersection(origin, rayDirection, minDist, maxDist, closestDistance, &closestSphere);

	if (closestSphere == nullptr)
	{
		rayDirection.Normalize();

		float u = rayDirection.x / 2 + 0.5f;
		float v = rayDirection.y / 2 + 0.5f;

		return ReadEnvironmentAtPixel(int(u * environmentMap.width), int(v * environmentMap.height));
	}

	const auto point = origin + rayDirection * closestDistance;
	auto norm = point - closestSphere->center;
	norm.Normalize();
	const Color localColor = closestSphere->color * ComputeLighting(point, norm, rayDirection * -1.0f, closestSphere->specular);

	// finish if recursion limit is hit or the object is not reflective
	if (recursionDepth <= 0 || closestSphere->reflectivity <= 0)
	{
		return localColor;
	}

	// compute reflected color
	const Vec3 reflectedRay = ReflectRay(rayDirection * -1.0f, norm);
	const Color reflectedColor = TraceRay(point, reflectedRay, 0.001f, std::numeric_limits<float>::infinity(), --recursionDepth);

	return localColor * (1 - closestSphere->reflectivity) + reflectedColor * closestSphere->reflectivity;
}

void Scene::LoadEnvironmentMap(const std::string& fileName)
{
	environmentMap = Texture{};

	auto* image = stbi_load(fileName.c_str(), &environmentMap.width, &environmentMap.height, &environmentMap.numChannels, 0);
	if (!image)
	{
		printf("Failed to load texture file %s \n", fileName.c_str() );
	}
	printf("Loaded image with a width of %ipx, a height of %ipx, and %i channels\n", environmentMap.width, environmentMap.height, environmentMap.numChannels);

	environmentMap.data = image;

	stbi_write_png("STBI_test.png", environmentMap.width, environmentMap.height, environmentMap.numChannels, environmentMap.data, 0);
}

Color Scene::ReadEnvironmentAtPixel(const int x, const int y)
{
	unsigned char* pixelOffset = environmentMap.data + (environmentMap.numChannels * ((environmentMap.height - 1 - y) * environmentMap.width + x));
	return {
		pixelOffset[0],
		pixelOffset[1],
		pixelOffset[2]
	};
}

float Scene::ComputeLighting(Vec3 point, Vec3 normal, Vec3 view, int specular)
{
	float intensity = 0.0f;
	const float normalLength = normal.Length();
	const float viewLength = view.Length();

	for (auto& light : lights)
	{
		if (light.type == Light::Ambient)
		{
			intensity += light.intensity;
		}
		else
		{
			Vec3 lightVector;
			float maxDist;
			if (light.type == Light::Point)
			{
				lightVector = light.position - point;
				maxDist = 1.0f;
			}
			else
			{
				lightVector = light.direction;
				maxDist = std::numeric_limits<float>::infinity();
			}

			// Shadow Check
			float shadowDist;
			Sphere* shadowSphere{};
			ClosestIntersection(point, lightVector, 0.001f, maxDist, shadowDist, &shadowSphere);
			if (shadowSphere != nullptr)
			{
				continue;
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
				Vec3 reflectionVector = ReflectRay(lightVector, normal);
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
