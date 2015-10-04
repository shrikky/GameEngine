#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "GameWindow.h"
#include "Shader.h"

const glm::vec2 SCREEN_SIZE(800, 600);

GameWindow *gameWindow;

int main(int argc, char**argv){
	gameWindow = new GameWindow(true);
	gameWindow->Init(glm::vec2(800, 600),"Shrikky's OpenGL");
	gameWindow->CreateTriangle();

	do{
		glfwPollEvents();
		gameWindow->setRunning(!glfwWindowShouldClose(gameWindow->window));
		glClear(GL_COLOR_BUFFER_BIT);

		gameWindow->render();
		gameWindow->update();
		glfwSwapBuffers(gameWindow->window);
	}
	while (glfwGetKey(gameWindow->window, GLFW_KEY_ESCAPE) != GLFW_PRESS && gameWindow->getRunning());

	delete gameWindow;


}

