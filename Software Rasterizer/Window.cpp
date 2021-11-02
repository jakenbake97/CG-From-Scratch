#include "Window.h"

Window::Window(const std::string& name)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not Initialize, Error: %s\n", SDL_GetError());
		return;
	}

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	if (window == nullptr)
	{
		printf("SDL could not create window, Error: %s\n", SDL_GetError());
		return;
	}

	surface = SDL_GetWindowSurface(window);
	if (surface == nullptr)
	{
		printf("SDL could not get window surface, Error: %s\n", SDL_GetError());
		return;
	}

	printf("Pixel Format: %s", SDL_GetPixelFormatName(surface->format->format));
	pixels = static_cast<unsigned int*>(surface->pixels);
}

Window::~Window()
{
	//Deallocate surface
	SDL_FreeSurface(surface);
	surface = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

void Window::PollEvents()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}

		if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				surface = SDL_GetWindowSurface(window);
				pixels = static_cast<Uint32*>(surface->pixels);
			}
		}
	}
}

SDL_Surface* Window::GetSurface() const
{
	return surface;
}

bool Window::ShouldRun() const
{
	return running;
}

void Window::PutPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) const
{
	pixels[x + y * surface->w] = SDL_MapRGB(surface->format, r, g, b);
}

void Window::Submit() const
{
	SDL_UpdateWindowSurface(window);
}
