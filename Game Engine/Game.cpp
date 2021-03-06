#include "Game.h"
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"



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

	shaderRenderList[0].Shader_RenderInit("shaders/simple_vert.glsl", "shaders/simple_frag.glsl");
	shaderRenderList[1].Shader_RenderInit("shaders/particle_vert.glsl", "shaders/particle_frag.glsl");
	
	shaderComputeList = new Shader;
	shaderComputeList[0].Shader_ComputeInit("shaders/particle_comp.glsl");

	particleSystem = new ParticleSystem;
	particleSystem->init();

	Model* model = new Model;
	modelList.push_back(model);
	modelList[0]->Model_Init("objects/cube/crate.obj");

	TransformManager::Instance()->create(0);
	TransformManager::Instance()->transformList[0]->translate(glm::vec3(4.0f, 0.0f, 0.0f));
	boxCollider = new Collider3D;
	boxCollider->createBoxCollider(1.0f, 1.0f, 1.0f, 0);

	RigidbodyManager::Instance()->create(0);

	cameraList = new Camera[2];
	cameraList[0].Camera_Init();
	cameraList[1].Camera_Init(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -90.0f);

	Model* model1 = new Model;
	modelList.push_back(model1);
	modelList[1]->Model_Init("objects/nanosuit/nanosuit.obj");
	TransformManager::Instance()->create(1);
	TransformManager::Instance()->transformList[1]->translate(glm::vec3(0.0f, -7.5f, 0.0f));

	TheSoundManager::Instance()->load("music/DST_ElectroRock.ogg", "music1", SOUND_MUSIC);
	TheSoundManager::Instance()->playMusic("music1", -1);

	lightManager.init(shaderRenderList[0].Program);
	lightManager.addLight(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(3.0f, 3.0f, 3.0f), LightType::POINT);
	lightManager.addLight(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(5.0f, 0.0f, 0.0f), LightType::DIRECTIONAL);
	lightManager.addLight(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 5.0f, 0.0f), LightType::DIRECTIONAL);
	lightManager.addLight(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 5.0f), LightType::DIRECTIONAL);

}

bool Game::handleEvents()
{
	return InputHandler::Instance()->update();
}

void Game::update(float t, const float dt)
{
	RigidbodyManager::Instance()->updateList(t, dt);
		
				/*if (Player::getInstance()->health > 0)
					cout << "You won" << endl;
				else
					cout << "Enemy won" << endl;*/
}

void Game::renderUpdate(const float dt)
{
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) 
	{
		RigidbodyManager::Instance()->rigidbodyList[0]->addMomentum(glm::vec3(0.0f, 0.0f, -0.1f));
	}

	if (Player::getInstance()->health > 0 && BlackBoardAI::Instance()->AIHEALTH > 0){

		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) && !isPressed){
			Player::getInstance()->Attack();
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_H) && !isPressed){
			Player::getInstance()->Hide();
		}

		_arbiter->Update();
		_ai->Update();
	}

	TransformManager::Instance()->updateList();
	ColliderManager::Instance()->updateList();
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 1024 / 2, 768);

	shaderRenderList[1].Use();
	cameraList[0].render(&shaderRenderList[1]);
	particleSystem->render(shaderRenderList[1].Program, shaderComputeList[0].Program);

	shaderRenderList[0].Use();
	cameraList[0].render(&shaderRenderList[0]);
	for (int i = 0; i < TransformManager::Instance()->transformList.size(); i++) {
		TransformManager::Instance()->transformList[i]->render(&shaderRenderList[0]);
		modelList[i]->Draw(shaderRenderList[0]);
	}

	glViewport(1024 / 2, 0, 1024 / 2, 768);
	shaderRenderList[1].Use();
	cameraList[1].render(&shaderRenderList[1]);
	particleSystem->render(shaderRenderList[1].Program, shaderComputeList[0].Program);

	shaderRenderList[0].Use();
	lightManager.setLights();
	cameraList[1].render(&shaderRenderList[0]);
	for (int i = 0; i < TransformManager::Instance()->transformList.size(); i++) {
		TransformManager::Instance()->transformList[i]->render(&shaderRenderList[0]);
		modelList[i]->Draw(shaderRenderList[0]);
	}
	//glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);

	GUIManager::Instance()->renderUI();
	windowContext.swapBuffers();
}

void Game::destroy()
{
	delete[] shaderRenderList;
	delete shaderComputeList;
	delete cameraList;
	windowContext.destroy();
}