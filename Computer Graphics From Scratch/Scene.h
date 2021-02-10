#pragma once
#include <vector>
#include "Camera.h"
#include "Sphere.h"

class Scene
{
public:
	Scene();
	Scene(Camera cam);

	void AddObjectToScene(Sphere newSphere);
	void CreateCamera(Vec3 position, Vec2 viewport, float nearPlane, Color clearColor);

	Vec2 RaySphereIntersection(const Vec3& origin, const Vec3& direction, const Sphere& sphere);
	Color TraceRay(Vec3 rayDirection, float minDist, float maxDist);
	
	std::vector<Sphere> objects;
	Camera camera;
};
