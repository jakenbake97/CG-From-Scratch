#pragma once
#include <vector>

#include "Color.h"
#include "Vector.h"

class Canvas
{
public:
	Canvas(unsigned int width, unsigned int height)
		: width(width), height(height), image(width * height * 4)
	{
	}

	Canvas(Vec2Int dimension)
		: width(dimension.x), height(dimension.y), image(width * height * 4)
	{
	}

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;
	Vec2Int GetDimensions() const;
	void PutPixel(int x, int y, Color color, int samplesPerPixel);
	void PutPixel(Vec2Int pos, Color color, int samplesPerPixel);
	Vec3 CanvasToViewport(Vec2Int pixel, Vec3 viewport) const;
	void SubmitImage(const char* fileName) const;
private:
	uint32_t width, height;
	std::vector<unsigned char> image;
};
