#include "Canvas.h"

#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
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

void Canvas::PutPixel(int x, int y, const Color color)
{
	const Vec2Int pixelPos = ConvertToCanvasSpace(x, y);
	
	if (pixelPos.x < 0 || pixelPos.x >= width || pixelPos.y < 0 || pixelPos.y >= height)
	{
		std::cout << "ERROR: pixelPos (" << pixelPos.x << ", " << pixelPos.y << ")" << std::endl;
		return;
	}

	auto offset = 4 * width * pixelPos.y + 4 * pixelPos.x;
	image[offset++] = color.r;
	image[offset++] = color.g;
	image[offset++] = color.b;
	image[offset] = color.a;
}

void Canvas::PutPixel(Vec2Int pos, Color color)
{
	PutPixel(pos.x, pos.y, color);
}

Vec2Int Canvas::ConvertToCanvasSpace(int x, int y) const
{
	return {(int)(width / 2) + x, (int)(height / 2) - y - 1};
}

Vec2Int Canvas::ConvertToCanvasSpace(Vec2Int pos) const
{
	return ConvertToCanvasSpace(pos.x, pos.y);
}

Vec3 Canvas::CanvasToViewport(Vec2Int pixel, Vec3 viewport) const
{
	return Vec3{pixel.x * viewport.x / (float)width, pixel.y * viewport.y / (float)height, viewport.z};
}

void Canvas::SubmitImage(const char* fileName) const
{
	const int success = stbi_write_png(fileName, width, height, 4, image.data(),0);

	if (!success)
	{
		printf("Failed to write image to png");
		return;
	}

	printf("Successfully wrote to png image");
}
