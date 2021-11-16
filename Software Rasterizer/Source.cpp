#include <SDL.h>

#include "Color.h"
#include "Vector.h"
#include "Window.h"

std::vector<int> Interpolate(const int i0, const int d0, const int i1, const int d1)
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
		values.push_back((int)std::round(d));
		d += m;
	}
	return values;
}

void DrawLine(Vec2Int p0, Vec2Int p1, const Color color, const Window& window)
{
	if (abs(p1.x - p0.x) > abs(p1.y - p0.y)) // Line is more horizontal than vertical
	{
		if (p1.x < p0.x) // swap so that the lesser X is first
		{
			swap(p0, p1);
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
			swap(p0, p1);
		}

		const auto xValues = Interpolate(p0.y, p0.x, p1.y, p1.x);
		for (int y = p0.y; y <= p1.y; y++)
		{
			window.PutPixel(xValues[static_cast<size_t>(y) - p0.y], y, color);
		}
	}
}

void DrawWireframeTriangle(const Vec2Int p0, const Vec2Int p1, const Vec2Int p2, const Color color, const Window& window)
{
	DrawLine(p0, p1, color, window);
	DrawLine(p1, p2, color, window);
	DrawLine(p2, p0, color, window);
}

void DrawFilledTriangle(Vec2Int p0, Vec2Int p1, Vec2Int p2, const Color color, const Window& window)
{
	if (p1.y < p0.y) swap(p1, p0);
	if (p2.y < p0.y) swap(p2, p0);
	if (p2.y < p1.y) swap(p2, p1);

	std::vector<int> xLeft, xRight;
	{ // create scope so that there aren't as many vectors hanging around
		auto x01 = Interpolate(p0.y, p0.x, p1.y, p1.x);
		auto x12 = Interpolate(p1.y, p1.x, p2.y, p2.x);
		const auto x02 = Interpolate(p0.y, p0.x, p2.y, p2.x);

		// remove the duplicate entry on the 0 to 1 and 1 to 2 sides of the triangle
		x01.pop_back();

		// concatenate the two short side vectors
		std::vector<int> x012(x01);
		x012.insert(x012.end(), x12.begin(), x12.end());

		const auto m = (int)floorf((float)x02.size() / 2.0f);
		if (x02[m] < x012[m])
		{
			xLeft = x02;
			xRight = x012;
		}
		else
		{
			xLeft = x012;
			xRight = x02;
		}
	}

	for (int y = p0.y; y < p2.y; y++)
	{
		for (int x = xLeft[static_cast<size_t>(y) - p0.y]; x <= xRight[static_cast<size_t>(y) - p0.y]; x++)
		{
			window.PutPixel(x, y, color);
		}
	}
}

int main(int argc, char* args[])
{
	Window window("Main Window");

	const Vec2Int point0(100, 100);
	const Vec2Int point1(215, 400);
	const Vec2Int point2(200, 75);

	while (window.ShouldRun())
	{
		window.PollEvents();
		DrawWireframeTriangle(point0, point1, point2, { 255, 255, 100 }, window);
		DrawFilledTriangle(point0, point1, point2, { 255, 100, 255 }, window);
		window.Submit();
	}

	return 0;
}
