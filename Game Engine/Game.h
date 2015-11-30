#pragma once

#include "WindowContext.h"
#include "InputHandler.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "TransformManager.h"
#include "RigidbodyManager.h"
#include "ParticleSystem.h"
#include "SoundManager.h"
#include "LightManager.h"

#include <vector>
class Game
{
public:
	Game();
	~Game();

	void init(const char *title, const int width, const int height, int flags);
	bool handleEvents();
	void update(float t, const float dt);
	void renderUpdate(const float dt);
	void render();
	void destroy();
private:
	WindowContext windowContext;
	int gameObjectCount;
	Shader* shaderRenderList;
	Shader* shaderComputeList;
	ParticleSystem *particleSystem;
	std::vector<Model*> modelList;
	Camera* cameraList;
	LightManager lightManager;

};