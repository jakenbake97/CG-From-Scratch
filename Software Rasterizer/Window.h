#pragma once
#include <SDL.h>
#include <string>

class Window
{
public:
	Window(const std::string& name);
	~Window();
	void PollEvents();
	SDL_Surface* GetSurface() const;
	bool ShouldRun() const;
	void PutPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) const;
	void Submit() const;

	int GetWidth() const { return surface->w; }
	int GetHeight() const { return surface->h; }
private:
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Event event;
	bool running = true;
	Uint32* pixels;
};