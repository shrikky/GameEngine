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

	shaderRenderList = new Shader[2];
	shaderComputeList = new Shader; 

	shaderRenderList[0].Shader_RenderInit("shaders/simple_vert.glsl", "shaders/simple_frag.glsl");
	shaderRenderList[1].Shader_RenderInit("shaders/particle_vert.glsl", "shaders/particle_frag.glsl");

	shaderComputeList[0].Shader_ComputeInit("shaders/particle_comp.glsl");

	modelList = new Model;
	modelList->Model_Init("objects/nanosuit/nanosuit.obj");

	transformList = new Transform;
	transformList->create();
	transformList->translate(glm::vec3(0.0f, -7.5f, 0.0f));

	cameraList = new Camera;
	cameraList->Camera_Init();
	
	particleSystem = new ParticleSystem;
	particleSystem->init();
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
	transformList->update();
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderRenderList[1].Use();
	glUniformMatrix4fv(glGetUniformLocation(shaderRenderList[1].Program, "view"), 1, GL_FALSE, glm::value_ptr(cameraList->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shaderRenderList[1].Program, "projection"), 1, GL_FALSE, glm::value_ptr(glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f)));
	particleSystem->render(shaderRenderList[1].Program, shaderComputeList[0].Program);

	shaderRenderList[0].Use();
	glUniformMatrix4fv(glGetUniformLocation(shaderRenderList[0].Program, "model"), 1, GL_FALSE, glm::value_ptr(transformList->returnModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shaderRenderList[0].Program, "view"), 1, GL_FALSE, glm::value_ptr(cameraList->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shaderRenderList[0].Program, "projection"), 1, GL_FALSE, glm::value_ptr(glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f)));
	modelList->Draw(shaderRenderList[0]);

	windowContext.swapBuffers();
}

void Game::destroy()
{
	delete modelList;
	delete shaderRenderList;
	delete transformList;
	delete cameraList;
	windowContext.destroy();
}