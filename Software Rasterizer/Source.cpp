#include <SDL.h>

#include "Camera.h"
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

std::vector<float> Interpolate(const int i0, const float d0, const int i1, const float d1)
{
	std::vector<float> values;
	if (i0 == i1)
	{
		return { d0 };
	}
	const float m = (d1 - d0) / float(i1 - i0);
	float d = d0;
	for (int i = i0; i <= i1; i++)
	{
		values.push_back(d);
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

		const int m = (int)x02.size() / 2;
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

void DrawShadedTriangle(Vec2Int p0, float hue0, Vec2Int p1, float hue1,  Vec2Int p2, float hue2, const Color color, const Window& window)
{
	if (p1.y < p0.y) swap(p1, p0);
	if (p2.y < p0.y) swap(p2, p0);
	if (p2.y < p1.y) swap(p2, p1);

	std::vector<int> xLeft, xRight;
	std::vector<float> hueLeft, hueRight;
	{ // create scope so that there aren't as many vectors hanging around
		auto x01 = Interpolate(p0.y, p0.x, p1.y, p1.x);
		auto hue01 = Interpolate(p0.y, hue0, p1.y, hue1);
		auto x12 = Interpolate(p1.y, p1.x, p2.y, p2.x);
		auto hue12 = Interpolate(p1.y, hue1, p2.y, hue2);
		const auto x02 = Interpolate(p0.y, p0.x, p2.y, p2.x);
		const auto hue02 = Interpolate(p0.y, hue0, p2.y, hue2);

		// remove the duplicate entry on the 0 to 1 and 1 to 2 sides of the triangle
		x01.pop_back();

		// concatenate the two short side vectors
		std::vector<int> x012(x01);
		x012.insert(x012.end(), x12.begin(), x12.end());

		std::vector<float> hue012(hue01);
		hue012.insert(hue012.end(), hue12.begin(), hue12.end());

		const int m = (int)x02.size() / 2;
		if (x02[m] < x012[m])
		{
			xLeft = x02;
			hueLeft = hue02;

			xRight = x012;
			hueRight = hue012;
		}
		else
		{
			xLeft = x012;
			hueLeft = hue012;

			xRight = x02;
			hueRight = hue02;
		}
	}

	for (int y = p0.y; y < p2.y; y++)
	{
		int xL = xLeft[static_cast<size_t>(y) - p0.y];
		int xR = xRight[static_cast<size_t>(y) - p0.y];
		auto hueSegment = Interpolate(xL, hueLeft[static_cast<size_t>(y) - p0.y], xR, hueRight[static_cast<size_t>(y) - p0.y]);

		for (int x = xL; x <= xR; x++)
		{
			const Color shadedColor = color * hueSegment[static_cast<size_t>(x) - xL];
			window.PutPixel(x, y, shadedColor);
		}
	}
}

int main(int argc, char* args[])
{
	Window window("Main Window");
	Camera cam(Vec3(0.0f), 1.0f, 1.0f);

	// The four "front" vertice
	const Vec3 vertAFront(-2.0f, -0.5f, 5.0f);
	const Vec3 vertBFront(-2.0f, 0.5f, 5.0f);
	const Vec3 vertCFront(-1.0f, 0.5f, 5.0f);
	const Vec3 vertDFront(-1.0f, -0.5f, 5.0f);

	// The four "Back" vertice
	const Vec3 vertABack(-2.0f, -0.5f, 6.0f);
	const Vec3 vertBBack(-2.0f, 0.5f, 6.0f);
	const Vec3 vertCBack(-1.0f, 0.5f, 6.0f);
	const Vec3 vertDBack(-1.0f, -0.5f, 6.0f);

	while (window.ShouldRun())
	{
		window.PollEvents();


		// The front face
		DrawLine(cam.ProjectVertex(vertAFront, window), cam.ProjectVertex(vertBFront, window), { 0.0f, 0.0f, 1.0f }, window);
		DrawLine(cam.ProjectVertex(vertBFront, window), cam.ProjectVertex(vertCFront, window), { 0.0f, 0.0f, 1.0f }, window);
		DrawLine(cam.ProjectVertex(vertCFront, window), cam.ProjectVertex(vertDFront, window), { 0.0f, 0.0f, 1.0f }, window);
		DrawLine(cam.ProjectVertex(vertDFront, window), cam.ProjectVertex(vertAFront, window), { 0.0f, 0.0f, 1.0f }, window);

		// The back face
		DrawLine(cam.ProjectVertex(vertABack, window), cam.ProjectVertex(vertBBack, window), { 1.0f, 0.0f, 0.0f }, window);
		DrawLine(cam.ProjectVertex(vertBBack, window), cam.ProjectVertex(vertCBack, window), { 1.0f, 0.0f, 0.0f }, window);
		DrawLine(cam.ProjectVertex(vertCBack, window), cam.ProjectVertex(vertDBack, window), { 1.0f, 0.0f, 0.0f }, window);
		DrawLine(cam.ProjectVertex(vertDBack, window), cam.ProjectVertex(vertABack, window), { 1.0f, 0.0f, 0.0f }, window);

		// The front-to-back edges
		DrawLine(cam.ProjectVertex(vertAFront, window), cam.ProjectVertex(vertABack, window), { 0.0f, 1.0f, 0.0f }, window);
		DrawLine(cam.ProjectVertex(vertBFront, window), cam.ProjectVertex(vertBBack, window), { 0.0f, 1.0f, 0.0f }, window);
		DrawLine(cam.ProjectVertex(vertCFront, window), cam.ProjectVertex(vertCBack, window), { 0.0f, 1.0f, 0.0f }, window);
		DrawLine(cam.ProjectVertex(vertDFront, window), cam.ProjectVertex(vertDBack, window), { 0.0f, 1.0f, 0.0f }, window);


		window.Submit();
	}

	return 0;
}
