#pragma once
#include <vector>
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"

class Scene
{
public:
	Scene();
	Scene(Camera cam);

	void AddObjectToScene(Sphere newSphere);
	void AddLightToScene(Light light);
	void CreateCamera(Vec3 position, Vec2 viewport, float nearPlane, Color clearColor);

	static Vec2 RaySphereIntersection(const Vec3& origin, const Vec3& direction, const Sphere& sphere);
	Color TraceRay(Vec3 rayDirection, float minDist, float maxDist);
	
	Camera camera;
private:
	std::vector<Sphere> objects;
	std::vector<Light> lights;

	float ComputeLighting(Vec3 point, Vec3 normal, Vec3 view, int specular);
};
