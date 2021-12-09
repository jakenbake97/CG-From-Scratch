#pragma once
#include "Vector.h"

class Window;

class Camera
{
public:
	Camera() = default;
	Camera(Vec3 position, float viewportSize, float farPlane);

	Vec2Int ProjectVertex(Vec3 vertex, const Window& window) const;

	Vec3 position;
	Vec3 viewportSize;
};
