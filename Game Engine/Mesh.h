#pragma once
#include <GL\glew.h>
#include "Vector.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct Vertex{
	vec3 v_position;
	vec3 v_normal;
	vec3 v_texcoords;

} Vertex;

typedef struct Texture{

	GLuint id;
	char *type;
}Texture;

class Mesh
{
public:
	Mesh();
	~Mesh();
	Vertex * vertices;
	int num_vertices;

	GLuint* indices;
	int num_indices;

	Texture* textures;
	int num_textures;

	GLuint vao;
	GLuint vbo;
	GLuint ebo;


	void Mesh_init(const char* Obj_file, const int obj_data[6]);
	void Mesh_LoadTexture(Mesh *mesh, const char* text_path, const char *text_type);
	void Mesh_Setup(Shader* shader);
	void Mesh_Render(Shader* shader);
	void Mesh_Destroy();
};

