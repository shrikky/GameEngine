#pragma once

#include <SDL/SDL.h>

class WindowContext
{
public:
	WindowContext();
	~WindowContext();

	void init(const char *title, int width, int height, int flags);
	void swapBuffers();
	void destroy();
	SDL_Window* getWindow();
private:
	SDL_Window *window;
	SDL_GLContext glContext;
};

