#pragma once
#include <SDL.h>
#include <string>

#include "Vector.h"

class Color;

class Window
{
public:
	Window(const std::string& name);
	~Window();
	void PollEvents();
	SDL_Surface* GetSurface() const;
	bool ShouldRun() const;
	void PutPixel(int x, int y, Color color) const;
	void Submit() const;
	Vec2Int ViewportToSurface(Vec3 point, Vec2 viewport) const;

	int GetWidth() const { return surface->w; }
	int GetHeight() const { return surface->h; }
private:
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Event event;
	bool running = true;
	Uint32* pixels;
};
