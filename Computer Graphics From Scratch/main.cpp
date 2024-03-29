#include "Utilities.h"
#include "Canvas.h"
#include "Scene.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "BVHNode.h"
#include "Dielectric.h"
#include "Lambertian.h"
#include "Metal.h"
#include "MovingSphere.h"
#include "stb_image_write.h"

std::unique_ptr<HittableList> RandomScene()
{
	std::unique_ptr<HittableList> randomList = std::make_unique<HittableList>();
	auto groundMat = std::make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f));
	randomList->Add(std::make_shared<Sphere>(Vec3(0, -1000, 0), 1000, groundMat));

	for (int a = -11; a < 11; ++a)
	{
		for (int b = -11; b < 11; ++b)
		{
			const float chooseMat = RandomValue();
			Vec3 center((float)a + 0.9f * RandomValue(), 0.2f, (float)b + 0.9f * RandomValue());

			if ((center - Vec3(4, 0.2f, 0)).Length() > 0.9f)
			{
				std::shared_ptr<Material> sphereMat;

				if (chooseMat < 0.8f)
				{
					// Diffuse
					Color albedo = Color::Random() * Color::Random();
					sphereMat = std::make_shared<Lambertian>(albedo);
					Vec3 center2;
					if (chooseMat < 0.3f)
						center2 = center + Vec3(0, RandomInRange(0.0f, 0.25f), 0);
					else
						center2 = center;
					
					randomList->Add(std::make_shared<MovingSphere>(center, center2, 0.0f, 1.0f, 0.2f, sphereMat));
				}
				else if (chooseMat < 0.95f)
				{
					// Metal
					Color albedo = Color::Random(0.5f, 1.0f);
					float roughness = RandomInRange(0.0f, 0.5f);
					sphereMat = std::make_shared<Metal>(albedo, roughness);
					randomList->Add(std::make_shared<Sphere>(center, 0.2f, sphereMat));
				}
				else
				{
					// Glass
					sphereMat = std::make_shared<Dielectric>(1.5f);
					randomList->Add(std::make_shared<Sphere>(center, 0.2f, sphereMat));
				}
			}
		}
	}

	auto glassMat = std::make_shared<Dielectric>(1.5f);
	randomList->Add(std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0f, glassMat));

	auto diffuseMat = std::make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
	randomList->Add(std::make_shared<Sphere>(Vec3(-4, 1, 0), 1.0f, diffuseMat));

	auto metalMat = std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
	randomList->Add(std::make_shared<Sphere>(Vec3(4, 1, 0), 1.0f, metalMat));

	return randomList;
}

int main()
{
	const float aspectRatio = 16.0f / 9.0f;
	const int imageWidth = 1920;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	const int samplesPerPixels = 10;
	const int maxDepth = 5;

	Canvas canvas(imageWidth, imageHeight);
	Vec3 camPosition = {13, 2, 3};
	Vec3 camTarget = {0, 0, 0};
	Camera cam(camPosition, camTarget, 20, aspectRatio, 0.1f, 10.0f, 1.0f);

	Scene mainScene;

	mainScene.world = BVHNode{*RandomScene(), 0.0f, 1.0f};
	
	mainScene.AddCam(cam);

	mainScene.LoadEnvironmentMap("Environments/dikhololo_night_1k.hdr");
	
	for (int j = 0; j < imageHeight; ++j)
	{
		printf("Lines remaining: %i  %.3f%%\n", imageHeight - 1 - j, (j / float(imageHeight - 1)) * 100.0f);
		for (int i = 0; i < imageWidth; ++i)
		{
			Color pixelColor(0.0f, 0.0f, 0.0f);

			for (int s = 0; s < samplesPerPixels; ++s)
			{
				const float u = ((float)i + RandomValue()) / (imageWidth - 1);
				const float v = ((float)j + RandomValue()) / (imageHeight - 1);

				Ray ray = cam.RayThroughViewport({u, v});
				pixelColor += mainScene.TraceRay(ray, maxDepth);
			}
			canvas.PutPixel(i, j, pixelColor, samplesPerPixels);
		}
	}

	canvas.SubmitImage("RayTracer_3.png");
	return 0;
}
