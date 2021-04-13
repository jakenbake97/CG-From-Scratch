#include "Scene.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Material.h"
#include "Ray.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "Utilities.h"

Scene::Scene() = default;

Scene::Scene(const Camera cam)
	: camera(cam)
{
}

void Scene::AddCam(const Camera cam)
{
	camera = cam;
}

Color Scene::TraceRay(Ray ray, int depth) const
{
	HitRecord rec;

	if (depth <= 0)
		return { 0,0,0 };
	
	if (world.Hit(ray, 0.001f, Infinity, rec))
	{
		Ray scattered;
		Color attenuation;
		rec.normal.Normalize();

		if (rec.material->Scatter(ray, rec, attenuation, scattered))
			return attenuation * TraceRay(scattered, depth - 1);
		
		return Color(0, 0, 0);
	}
	
	ray.direction.Normalize();
	float u = ray.direction.x / 2 + 0.5f;
	float v = ray.direction.y / 2 + 0.5f;

	return ReadEnvironmentAtPixel(int(u * (environmentMap.width - 1)), int(v * (environmentMap.height - 1)));
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
}

Color Scene::ReadEnvironmentAtPixel(const int x, const int y) const
{
	if (x < 0 || x >= environmentMap.width || y < 0 || y >= environmentMap.height)
	{
		printf("Invalid Pixel Location to read environment x:%i y:%i\n", x, y);
		return { 0,0,0 };
	}
	unsigned char* pixelOffset = environmentMap.data + (environmentMap.numChannels * ((environmentMap.height - 1 - y) * environmentMap.width + x));
	return {
		pixelOffset[0],
		pixelOffset[1],
		pixelOffset[2]
	};
}
