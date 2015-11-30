#include <SDL/SDL.h>
#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include <iostream>

#include "Game.h"

#define URL "http://www.google.com"
using namespace Awesomium;

int main(int argc, char* argv[])
{
	const float dt = 0.01f;
	float t = 0.0f;
	float accumulator = 0.0f;
	float current_time = 0.0f;
	bool quit_flag = 1;

	Game game;
	WebCore* web_core = WebCore::Initialize(WebConfig());
	WebView* view = web_core->CreateWebView(1024, 768);
	WebURL url(WSLit(URL));
	view->LoadURL(url);

	while (view->IsLoading())
		web_core->Update();
	Sleep(300);
	web_core->Update();

	BitmapSurface* surface = (BitmapSurface*)view->surface();

	if (surface != 0) {
		surface->SaveToJPEG(WSLit("./result.jpg"));
	}

	view->Destroy();
	WebCore::Shutdown();

	std::cout << "game init attempt...\n";
	game.init("OpenGL", 1024, 768, SDL_WINDOW_OPENGL);
	
	std::cout << "game init success!\n";
	while (quit_flag)
	{
		quit_flag = game.handleEvents();

		float new_time = (float)SDL_GetTicks() / 1000.0f;
		float delta_time = new_time - current_time;

		if (delta_time <= 0.0f)
			continue;

		current_time = new_time;

		accumulator += delta_time;
		while (accumulator >= dt)
		{
			game.update(t, dt);
			accumulator -= dt;
			t += dt;
		}

		game.renderUpdate(dt);
		game.render();
	}

	std::cout << "game closing...\n";
	game.destroy();
	return 0;
}