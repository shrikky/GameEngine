#pragma once

#include "WindowContext.h"
#include "GameObject.h"
#include "InputHandler.h"

#include "Shader.h"
#include "Model.h"
#include "Transform.h"
#include "Camera.h"

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
	Shader* shaderList;
	Model* modelList;
	Transform* transformList;
	Camera* cameraList;
};