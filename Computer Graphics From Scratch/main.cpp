#include "Canvas.h"

int main()
{
	Vec3 cameraPosition(0.0f,0.0f,0.0f);
	auto viewportSize = 1;
	auto projectionPlane = 1;
	Color backgroundColor(255,255,255,255);
	
	Canvas canvas(1920, 1080);
	for (int x = 0; x <= 255; ++x)
	{
		for (int y = 0; y <= 255; ++y)
		{
			canvas.PutPixel(x,y, {static_cast<unsigned char>(x),static_cast<unsigned char>(y),255,255});
		}
	}

	for (int x = -512; x <= -256; ++x)
	{
		for (int y = -512; y <= -256; ++y)
		{
			canvas.PutPixel(x,y, {255,static_cast<unsigned char>(y+512),static_cast<unsigned char>(x+512),255});
		}
	}
	
	canvas.SubmitImage();
}