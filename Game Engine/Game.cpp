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
	modelList->Model_Init("objects/cube/crate.obj");

	transformList = new Transform;
	transformList->create();
	TransformManager::Instance()->transformList.push_back(transformList);
	//transformList->translate(glm::vec3(0.0f, 0.0f, 0.0f));

	rigidBodyList = new Rigidbody;
	rigidBodyList->Rigidbody_Init();

	cameraList = new Camera;
	cameraList->Camera_Init();
	
}

bool Game::handleEvents()
{
	return InputHandler::Instance()->update();
}

void Game::update(float t, const float dt)
{
	rigidBodyList->update(t, dt);
}

void Game::renderUpdate(const float dt)
{
	transformList->update();
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shaderList->Use();
	transformList->render(shaderList);
	cameraList->render(shaderList);
	modelList->Draw(*shaderList);
	windowContext.swapBuffers();
}

void Game::destroy()
{
	delete modelList;
	delete shaderList;
	delete transformList;
	delete cameraList;
	delete rigidBodyList;
	windowContext.destroy();
}