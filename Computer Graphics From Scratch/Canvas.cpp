#include "Canvas.h"

#include <iostream>
#include "stb_image_write.h"

uint32_t Canvas::GetWidth() const
{
	return width;
}

uint32_t Canvas::GetHeight() const
{
	return height;
}

Vec2Int Canvas::GetDimensions() const
{
	return {(int)width, (int)height};
}

void Canvas::PutPixel(int x, int y, Color color, const int samplesPerPixel)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		printf("ERROR: Invalid pixel position (%i,%i)", x, y);
		return;
	}

	const auto scale = 1.0f / samplesPerPixel;
	auto r = sqrtf(color.r * scale);
	auto g = sqrtf(color.g * scale);
	auto b = sqrtf(color.b * scale);

	auto offset = 4 * ((height - 1 - y) * width + x);
	image[offset++] = static_cast<unsigned char>(ClampF(r * 255, 0, 255));
	image[offset++] = static_cast<unsigned char>(ClampF(g * 255, 0, 255));
	image[offset++] = static_cast<unsigned char>(ClampF(b * 255, 0, 255));
	image[offset] = 255;
}

void Canvas::PutPixel(const Vec2Int pos, Color color, const int samplesPerPixel)
{
	PutPixel(pos.x, pos.y, color, samplesPerPixel);
}

Vec3 Canvas::CanvasToViewport(Vec2Int pixel, Vec3 viewport) const
{
	return Vec3{pixel.x * viewport.x / (float)width, pixel.y * viewport.y / (float)height, viewport.z};
}

void Canvas::SubmitImage(const char* fileName) const
{
	const int success = stbi_write_png(fileName, width, height, 4, image.data(), 0);

	if (!success)
	{
		printf("Failed to write image to png");
		return;
	}

	printf("Successfully wrote to png image");
}
