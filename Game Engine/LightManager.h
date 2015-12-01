#pragma once
#include <GLM\gtc\type_ptr.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <sstream>

#define maxLights 10

enum LightType { POINT, DIRECTIONAL};
struct Light
{
	glm::vec4 position;
	glm::vec3 intensity;
};

class LightManager
{
private:

	Light lights[maxLights];
	GLuint uniLightPosition[maxLights];
	GLuint uniLightIntensity[maxLights];
	GLuint uniNumLights;
	GLuint numLights;
	void setUniformAttrib(GLuint* uniformVar, char* attribName, GLuint program);
public:
	LightManager();
	~LightManager();

	void init(GLuint program);
	void setLights();
	void addLight(glm::vec3 pos, glm::vec3 intensity, LightType type);
};

