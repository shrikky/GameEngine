#ifndef __Shader__
#define __Shader__

#include <GL/glew.h>
class Shader
{
public:
	GLuint program;
	Shader();
	~Shader();

	// Function to read shader contents from file into char buffer
	char *Shader_ReadFile(const GLchar *shaderpath);

	// Function to compile, create and return a shader program
	void Shader_CreateProg(const GLchar *vert_path, const GLchar *frag_path);

	// Function to use shader program
	void Shader_UseProg();

	// Function to unuse shader program
	void Shader_UnUseProg();

	// Funtion to delete shader program
	void Shader_DestroyProg(Shader *shader);

};

#endif
