#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "GameWindow.h"
#include "Shader.h"

const glm::vec2 SCREEN_SIZE(800, 600);

GameWindow *gameWindow;
bool keys[1024];
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
int main(int argc, char**argv){
	gameWindow = new GameWindow(true);
	gameWindow->Init(glm::vec2(800, 600),"Shrikky's OpenGL");
	glfwSetKeyCallback(gameWindow->window, key_callback);
	glfwSetCursorPosCallback(gameWindow->window, mouse_callback);
	glfwSetScrollCallback(gameWindow->window, scroll_callback);
	glfwSetInputMode(gameWindow->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	gameWindow->CreateTriangle();

	do{
		glfwPollEvents();
		do_movement();
		gameWindow->setRunning(!glfwWindowShouldClose(gameWindow->window));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gameWindow->render();
		gameWindow->update();
		glfwSwapBuffers(gameWindow->window);
	}
	while (glfwGetKey(gameWindow->window, GLFW_KEY_ESCAPE) != GLFW_PRESS && gameWindow->getRunning());

	delete gameWindow;


}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	GLfloat cameraSpeed = 0.01f;
	if (keys[GLFW_KEY_W])
		gameWindow->cameraPos += cameraSpeed * gameWindow->cameraFront;
	if (keys[GLFW_KEY_S])
		gameWindow->cameraPos -= cameraSpeed * gameWindow->cameraFront;
	if (keys[GLFW_KEY_A])
		gameWindow->cameraPos -= glm::normalize(glm::cross(gameWindow->cameraFront, gameWindow->cameraUp)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		gameWindow->cameraPos += glm::normalize(glm::cross(gameWindow->cameraFront, gameWindow->cameraUp)) * cameraSpeed;
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		gameWindow->lastX = xpos;
		gameWindow->lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - gameWindow->lastX;
	GLfloat yoffset = gameWindow->lastY - ypos;
	gameWindow->lastX = xpos;
	gameWindow->lastY = ypos;

	GLfloat sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	gameWindow->yaw += xoffset;
	gameWindow->pitch += yoffset;

	if (gameWindow->pitch > 89.0f)
		gameWindow->pitch = 89.0f;
	if (gameWindow->pitch < -89.0f)
		gameWindow->pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(gameWindow->yaw)) * cos(glm::radians(gameWindow->pitch));
	front.y = sin(glm::radians(gameWindow->pitch));
	front.z = sin(glm::radians(gameWindow->yaw)) * cos(glm::radians(gameWindow->pitch));
	gameWindow->cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (gameWindow->fov >= 1.0f && gameWindow->fov <= 45.0f)
		gameWindow->fov -= yoffset;
	if (gameWindow->fov <= 1.0f)
		gameWindow->fov = 1.0f;
	if (gameWindow->fov >= 45.0f)
		gameWindow->fov = 45.0f;
}