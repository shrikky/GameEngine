#pragma once
#include <iostream>

#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>
#include "Shader.h"

class GameWindow
{
private:
	bool _running;
	
public :
	GLuint VBO;
	GLuint VBO2;
	GLuint VAO;
	GLuint VAO2;
	GLFWwindow* window = NULL;
	void setRunning(bool newRunning);
	bool getRunning();
	GameWindow(bool running);
	~GameWindow();
	void render();
	void update();
	void Init(glm::vec2 ScreenSize, char* windowTitle);
	void CreateTriangle();
	Shader _shader;
	void DrawTriangle();


};

