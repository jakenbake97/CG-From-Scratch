#include "Camera.h"
#include "Window.h"

Camera::Camera(Vec3 position, float viewportSize, float farPlane)
	:position(position), viewportSize(viewportSize, viewportSize, farPlane)
{
}

Vec2Int Camera::ProjectVertex(Vec3 vertex, const Window& window) const
{
	return window.ViewportToSurface({ vertex.x * viewportSize.z / vertex.z, vertex.y * viewportSize.z / vertex.z, vertex.z }, { viewportSize.x, viewportSize.y });
}
