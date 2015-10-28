#include <SDL/SDL.h>

#include "Game.h"

#include <iostream>

int main(int argc, char* argv[])
{
	const float dt = 1.0f;
	float t = 0.0f;
	float accumulator = 0.0f;
	float current_time = 0.0f;
	bool quit_flag = 1;

	Game game;

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