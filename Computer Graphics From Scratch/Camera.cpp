#include "Camera.h"

Camera::Camera()
	: position(0,0,0), viewportSize(1,1), projectionPlaneDistance(1), clearColor(255,255,255,255)
{
}

Camera::Camera(Vec3 position, Vec2 viewport, float nearPlane, Color clearColor)
	: position(position), viewportSize(viewport), projectionPlaneDistance(nearPlane), clearColor(clearColor)
{
}
