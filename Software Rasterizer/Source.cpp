#include <cstdio>
#include <SDL.h>

#include "Color.h"
#include "Vector.h"
#include "Window.h"


void DrawLine(Vec2Int p0, Vec2Int p1, Color color, const Window& window)
{
	if (p1.x < p0.x)
	{
		const Vec2Int temp = p0;
		p0 = p1;
		p1 = temp;
	}

	float m = float(p1.y - p0.y) / float(p1.x - p0.x);
	float b = p0.y - m * p0.x;

	for (int x = p0.x; x <= p1.x; x++)
	{
		const int y = int(m * (float)x + b);
		window.PutPixel(x, y, color);
	}
}

int main(int argc, char* args[])
{
	Window window("Main Window");

	const Vec2Int point0(35, 100);
	const Vec2Int point1(500, 400);

	while (window.ShouldRun())
	{
		window.PollEvents();
		DrawLine(point0, point1, { 255, 255, 200 }, window);
		window.Submit();
	}

	return 0;
}
