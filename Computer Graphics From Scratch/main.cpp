#include "Canvas.h"
#include "Scene.h"
#include "Sphere.h"


int main()
{
	//Scene Setup
	Scene mainScene({{0.0f, 0.0f, 0.0f}, {1,1}, 1, {200,200,255,255}});

	mainScene.AddObjectToScene({{0, -1, 3}, 1, {255, 0, 0, 255}});
	mainScene.AddObjectToScene({{2, 0, 4}, 1, {0, 0, 255, 255}});
	mainScene.AddObjectToScene({{-2, 0, 4}, 1, {0, 255, 0, 255}});
	
	Canvas canvas(1024, 1024);
	const Vec3 viewport = {mainScene.camera.viewportSize.x, mainScene.camera.viewportSize.y, mainScene.camera.projectionPlaneDistance};

	for (int x = -(int)(canvas.GetWidth()/2); x < (int)(canvas.GetWidth()/2); ++x)
	{
		for (int y = (int)(canvas.GetHeight()/2); y > -(int)(canvas.GetHeight()/2); --y)
		{
			const Vec3 viewportPoint = canvas.CanvasToViewport({x,y}, viewport);

			const auto& rayDirection = viewportPoint - mainScene.camera.position;
			const Color color = mainScene.TraceRay(viewportPoint, 1, std::numeric_limits<float>::infinity());

			canvas.PutPixel(x,y, color);
		}
	}
	
	canvas.SubmitImage();
}


