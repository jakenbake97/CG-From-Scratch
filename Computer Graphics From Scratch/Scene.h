#pragma once
#include <string>
#include <vector>
#include "Camera.h"
#include "HittableList.h"
#include "Light.h"
#include "Sphere.h"

class Scene
{
public:
	Scene();
	Scene(Camera cam);

	void AddCam(Camera cam);
	Color TraceRay(Ray ray, int depth) const;

	void LoadEnvironmentMap(const std::string& fileName);
	Color ReadEnvironmentAtPixel(int x, int y) const;
	
	Camera camera;
	struct Texture
	{
		int width, height, numChannels;
		unsigned char* data;
	} environmentMap{};

public:
	HittableList world{};
};
