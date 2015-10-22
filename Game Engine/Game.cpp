#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, const int width, const int height, int flags)
{
	windowContext.init(title, width, height, flags);
	gameObjectCount = 1;


}

bool Game::handleEvents()
{
	return InputHandler::Instance()->update();
}

void Game::update(float t, const float dt)
{

}

void Game::renderUpdate(const float dt)
{

}

void Game::render()
{
	windowContext.swapBuffers();
}

void Game::destroy()
{
	windowContext.destroy();
}