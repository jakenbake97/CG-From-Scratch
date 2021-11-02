#include <cstdio>
#include <SDL.h>

#include "Window.h"

int main(int argc, char* args[])
{
	Window window("Main Window");

	while (window.ShouldRun())
	{
		window.PollEvents();



		window.Submit();
	}

	return 0;
}
