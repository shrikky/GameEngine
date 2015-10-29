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

	Model* model = new Model;
	modelList.push_back(model);
	modelList[0]->Model_Init("objects/cube/crate.obj");

	TransformManager::Instance()->create(0);
	TransformManager::Instance()->transformList[0]->translate(glm::vec3(4.0f, 0.0f, 0.0f));

	RigidbodyManager::Instance()->create(0);

	cameraList = new Camera;
	cameraList->Camera_Init();

	Model* model1 = new Model;
	modelList.push_back(model1);
	modelList[1]->Model_Init("objects/nanosuit/nanosuit.obj");
	TransformManager::Instance()->create(1);
	TransformManager::Instance()->transformList[1]->translate(glm::vec3(0.0f, -7.5f, 0.0f));
	
}

bool Game::handleEvents()
{
	return InputHandler::Instance()->update();
}

void Game::update(float t, const float dt)
{
	RigidbodyManager::Instance()->updateList(t, dt);
	//rigidBodyList->update(t, dt);
}

void Game::renderUpdate(const float dt)
{
	//replace 0 with id
	for (int i = 0; i < TransformManager::Instance()->transformList.size(); i++) {
		TransformManager::Instance()->transformList[i]->update();
	}
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shaderList->Use();
	cameraList->render(shaderList);
	vector <Transform*> tempList = TransformManager::Instance()->transformList;
	for (int i = 0; i < TransformManager::Instance()->transformList.size(); i++) {
		TransformManager::Instance()->transformList[i]->render(shaderList);
		modelList[i]->Draw(*shaderList);
	}
	windowContext.swapBuffers();
}

void Game::destroy()
{
	delete shaderList;
	delete cameraList;
	windowContext.destroy();
}