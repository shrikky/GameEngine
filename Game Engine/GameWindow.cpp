#include "GameWindow.h"

void GameWindow::setRunning(bool newRunning){
	_running = newRunning;

}
bool GameWindow::getRunning(){
	return _running;
}

GameWindow::GameWindow(bool running){
	_running = running;
}
void GameWindow::render(){

	glClear(GL_COLOR_BUFFER_BIT);
	this->DrawTriangle();
	glfwSwapBuffers(this->window);
}
void GameWindow::update(){

}
void OnError(int errorCode, const char* msg) {
	throw std::runtime_error(msg);
}
void GameWindow::Init(glm::vec2 ScreenSize, char* windowTitle){

	glfwInit();
	glfwSetErrorCallback(OnError);
	if (!glfwInit())
		throw std::runtime_error("glfwInit failed");

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	this->window = glfwCreateWindow((int)ScreenSize.x, (int)ScreenSize.y, windowTitle, NULL, NULL);

	if (!this->window)
		throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");

	// GLFW settings
	glfwMakeContextCurrent(this->window);
	glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("glewInit failed");
}

GameWindow::~GameWindow(){
	glfwTerminate();
	std::cout << "DESTRUCTSHAAAN" << std::endl;
}
void GameWindow:: CreateTriangle(){
	GLfloat vertices[] = {

		0.5f, 0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, 0.5f, 0.0f,  // Top Left 
		// Second triangle
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f, 0.5f, 0.0f
	};
	GLfloat indices[] = {
		0, 1, 3,
		1, 2, 3

	};
	
	_shader.Shader_CreateProg("simple_vert.glslv", "simple_frag.glslf");
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glBindVertexArray(0);
}

//void Test(){
//		GLfloat vertices[] = {
//			-0.5f, -0.5f, 0.0f,
//			0.5f, -0.5f, 0.0f,
//			0.0f, 0.5f, 0.0f
//		};
//
//		GLfloat vertices2[] = {
//			-0.5f, 0.5f, 0.0f,
//			0.0f, -0.5f, 0.0f,
//			0.5f, 0.5f, 0.0f
//		};
//
//
//		_shader.Shader_CreateProg("simple_vert.glslv", "simple_frag.glslf");
//
//		glGenBuffers(1, &VBO);
//		glGenVertexArrays(1, &VAO);
//		glBindVertexArray(VAO);
//		glEnableVertexAttribArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//
//		glGenBuffers(1, &VBO2);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//
//
//		glBindVertexArray(0);
//
//		/*glGenBuffers(1, &VBO2);
//		glGenVertexArrays(1, &VAO2);
//		glBindVertexArray(VAO2);
//		glEnableVertexAttribArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//		glBindVertexArray(0);*/
//}
void GameWindow::DrawTriangle(){ 

	_shader.Shader_UseProg();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	/*glBindVertexArray(VAO2);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);*/
}


