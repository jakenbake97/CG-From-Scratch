#pragma once
#include "Color.h"
#include "Vector.h"

class Camera
{
public:
	Camera();
	Camera(Vec3 position, Vec2 viewport, float nearPlane, Color clearColor);
	
	Vec3 position;
	Vec2 viewportSize;
	float projectionPlaneDistance;
	Color clearColor;
};
