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
	gameObjectCount = 0;

	shaderList = new Shader;


	shaderList->Shader_Init("shaders/simple_vert.glsl", "shaders/simple_frag.glsl");

	modelList = new Model;
	modelList->Model_Init("objects/nanosuit/nanosuit.obj");

	transformList = new Transform;
	transformList->create();

	cameraList = new Camera;
	cameraList->Camera_Init();
	
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shaderList->Use();
	glUniformMatrix4fv(glGetUniformLocation(shaderList->Program, "model"), 1, GL_FALSE, glm::value_ptr(transformList->returnModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shaderList->Program, "view"), 1, GL_FALSE, glm::value_ptr(cameraList->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shaderList->Program, "projection"), 1, GL_FALSE, glm::value_ptr(glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f)));
	modelList->Draw(*shaderList);
	windowContext.swapBuffers();
}

void Game::destroy()
{
	delete modelList;
	delete shaderList;
	delete transformList;
	delete cameraList;
	windowContext.destroy();
}