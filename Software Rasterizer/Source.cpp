#include <cstdio>
#include <SDL.h>

#include "Color.h"
#include "Vector.h"
#include "Window.h"

std::vector<int> Interpolate(int i0, int d0, int i1, int d1)
{
	std::vector<int> values;
	if (i0 == i1)
	{
		return { d0 };
	}
	const float m = float(d1 - d0) / float(i1 - i0);
	auto d = (float)d0;
	for (int i = i0; i <= i1; i++)
	{
		values.push_back(std::round(d));
		d += m;
	}
	return values;
}

void DrawLine(Vec2Int p0, Vec2Int p1, Color color, const Window& window)
{
	if (abs(p1.x - p0.x) > abs(p1.y - p0.y)) // Line is more horizontal than vertical
	{
		if (p1.x < p0.x) // swap so that the lesser X is first
		{
			const Vec2Int temp = p0;
			p0 = p1;
			p1 = temp;
		}

		const auto yValues = Interpolate(p0.x, p0.y, p1.x, p1.y);
		for (int x = p0.x; x <= p1.x; x++)
		{
			window.PutPixel(x, yValues[static_cast<size_t>(x) - p0.x], color);
		}
	}
	else // Line is more vertical than horizontal
	{
		if (p1.y < p0.y) // swap so the lesser Y is first
		{
			const Vec2Int temp = p0;
			p0 = p1;
			p1 = temp;
		}

		const auto xValues = Interpolate(p0.y, p0.x, p1.y, p1.x);
		for (int y = p0.y; y <= p1.y; y++)
		{
			window.PutPixel(xValues[static_cast<size_t>(y) - p0.y], y, color);
		}
	}
	
}

int main(int argc, char* args[])
{
	Window window("Main Window");

	const Vec2Int point0(35, 100);
	const Vec2Int point1(35, 400);
	const Vec2Int point2(200, 75);

	while (window.ShouldRun())
	{
		window.PollEvents();
		DrawLine(point0, point1, { 255, 255, 200 }, window);
		DrawLine(point1, point2, { 0, 200, 40 }, window);
		DrawLine(point2, point0, { 20, 20, 255 }, window);
		window.Submit();
	}

	return 0;
}
