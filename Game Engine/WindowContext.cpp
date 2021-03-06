#include "WindowContext.h"

#include <GL/glew.h>
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include <assert.h>
#include <stdio.h>

WindowContext::WindowContext()
{
}

WindowContext::~WindowContext()
{
}

void WindowContext::init(const char *title, int width, int height, int flags)
{
	// Sdl initialization
	SDL_Init(SDL_INIT_EVERYTHING);

	// Setting opengl version
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	// Creating Window
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	// Setting context of the window
	glContext = SDL_GL_CreateContext(window);

	// Glew initialization
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	assert(err == GLEW_OK);

	ImGui_ImplSdlGL3_Init(window);
	// Print opengl version
	printf("Using opengl version %s.\n", glGetString(GL_VERSION));
	printf("Using glsl version %s.\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
}

void WindowContext::swapBuffers()
{
	SDL_GL_SwapWindow(window);
}

void WindowContext::destroy()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
}

SDL_Window* WindowContext::getWindow() {
	return window;
}