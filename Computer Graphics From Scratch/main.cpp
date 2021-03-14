#include "Canvas.h"
#include "Scene.h"
#include "Sphere.h"


int main()
{
	//Scene Setup
	Scene mainScene({{0.0f, 0.0f, 0.0f}, {1,1}, 1, {200,200,255,255}});
	
	Sphere redSphere{};
	redSphere.center = {0, -1, 3};
	redSphere.radius = 1;
	redSphere.color = {255,0,0};
	redSphere.specular = 500;
	redSphere.reflectivity = 0.2f;
	mainScene.AddObjectToScene(&redSphere);

	Sphere blueSphere{};
	blueSphere.center = {2, 0, 4};
	blueSphere.radius = 1;
	blueSphere.color = {0,0,255};
	blueSphere.specular = 500;
	blueSphere.reflectivity = 0.3f;
	mainScene.AddObjectToScene(&blueSphere);

	Sphere greenSphere{};
	greenSphere.center = {-2, 0, 4};
	greenSphere.radius = 1;
	greenSphere.color = {0, 255, 0};
	greenSphere.specular = 10;
	greenSphere.reflectivity = 0.4f;
	mainScene.AddObjectToScene(&greenSphere);

	Sphere groundSphere{};
	groundSphere.center = {0, -5001, 0};
	groundSphere.radius = 5000;
	groundSphere.color = {255, 255, 0};
	groundSphere.specular = 1000;
	groundSphere.reflectivity = 0.5f;
	mainScene.AddObjectToScene(&groundSphere);

	mainScene.AddLightToScene({Light::Ambient, 0.2f});
	mainScene.AddLightToScene({Light::Point, 0.6f, {2,1,0}} );
	mainScene.AddLightToScene({Light::Directional, 0.6f, {1,4,4}} );
	
	Canvas canvas(1024, 1024);
	const Vec3 viewport = {mainScene.camera.viewportSize.x, mainScene.camera.viewportSize.y, mainScene.camera.projectionPlaneDistance};

	for (int x = -(int)(canvas.GetWidth()/2); x < (int)(canvas.GetWidth()/2); ++x)
	{
		for (int y = -(int)(canvas.GetHeight()/2); y < (int)(canvas.GetHeight()/2); ++y)
		{
			const Vec3 viewportPoint = canvas.CanvasToViewport({x,y}, viewport);

			const Color color = mainScene.TraceRay(mainScene.camera.position, viewportPoint, 1, std::numeric_limits<float>::infinity(), 3);

			canvas.PutPixel(x,y, color);
		}
	}
	
	canvas.SubmitImage();
}


