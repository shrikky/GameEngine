
// third-party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Mesh.h"
#include "Camera.h"
#include "Transformations.h"
using namespace std;
// globals
// constants
const glm::vec2 SCR0EEN_SIZE(800, 600);

GLFWwindow* window = NULL;

GLuint gVAO = 0;
GLuint gVBO = 0;
int obj_data[6] = { 16, 48, 48, 72, 72, 1 };
Mesh object;
Camera mainCam;
Shader _shader;
Transformations _transform;

glm::mat4 modelMatrix ;
glm::mat4 perspectiveMatrix;
glm::mat4 viewMatrix;

void OnError(int errorCode, const char* msg) {
	throw std::runtime_error(msg);
}

void LoadWindow(bool fullscreen) {
	// initialise GLFW
	glfwSetErrorCallback(OnError);
	if (!glfwInit())
		throw std::runtime_error("glfwInit failed");

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	if (fullscreen)
		window = glfwCreateWindow((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y, "OpenGL Tutorial", glfwGetPrimaryMonitor(), NULL);
	else
		window = glfwCreateWindow((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y, "OpenGL Tutorial", NULL, NULL);

	if (!window)
		throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");

	// GLFW settings
	glfwMakeContextCurrent(window); 
	glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("glewInit failed");

}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	GLfloat objectSpeed = 0.05f;
	if (key == GLFW_KEY_W)
	{
		glm::vec3 posis = objectSpeed * glm::vec3(0.0, 0.0f, -1.0f);
		_transform.UpdatePosition(posis);
	}
	if (key == GLFW_KEY_S){
		glm::vec3 posis = objectSpeed * glm::vec3(0.0, 0.0f, 1.0f);
		_transform.UpdatePosition(posis);
	}


}
int main() {

	double lastTime = glfwGetTime();
	int numFrames = 0;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	LoadWindow(false);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	_shader.Shader_CreateProg("simple_vert.glslv", "simple_frag.glslf");
	mainCam.InitCamera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	perspectiveMatrix = mainCam.ReturnPerspective(45.0,(800.0f/600.0f), 0.1f, 100.0f);
	viewMatrix = mainCam.ReturnView();
	_transform.TransformInit(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f), glm::vec3(0.0f,0.0f,0.0f));
	glfwSetKeyCallback(window, key_callback);
	int perspPos = glGetUniformLocation(_shader.program, "perspectiveMatrix");
	int viewpos = glGetUniformLocation(_shader.program, "viewMatrix");
	int matpos = glGetUniformLocation(_shader.program, "modelMatrix");
	object.Mesh_init("cube.obj", obj_data);
	object.Mesh_Setup(&_shader);
	_shader.Shader_UseProg();
	glUniformMatrix4fv(perspPos, 1, false, glm::value_ptr(perspectiveMatrix));
	glUniformMatrix4fv(viewpos, 1, false, glm::value_ptr(viewMatrix));
	
	glBindVertexArray(gVAO);
	do {

		double currentTime = glfwGetTime();
		numFrames++;
		if (currentTime - lastTime >= 1.0f){
			printf("%f ms/frame\n",  1000.0/ double(numFrames));
			numFrames = 0;
			lastTime += 1.0;
		}

		glClear(GL_COLOR_BUFFER_BIT);
		// Swap Buffers
		glUniformMatrix4fv(matpos, 1, false, glm::value_ptr(_transform.ReturnModelMatrix()));
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		object.Mesh_Render(&_shader);
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);





}