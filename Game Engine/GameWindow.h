#pragma once
#include <iostream>

#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include "Shader.h"
class GameWindow
{
private:
	bool _running;
	
public :
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	GLuint texture1;
	GLuint texture2;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	GLfloat pitch = 0.0f;
	GLfloat lastX = 800.0f / 2.0;
	GLfloat lastY = 600.0f / 2.0;
	GLfloat fov = 45.0f;
	bool keys[1024];
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

