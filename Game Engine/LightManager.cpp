#include "LightManager.h"


LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}


void LightManager::init(GLuint program)
{
	numLights = 0;
	setUniformAttrib(uniLightPosition, "position", program);
	setUniformAttrib(uniLightIntensity, "intensity", program);
	uniNumLights = glGetUniformLocation(program, "numLights");
}

// Gets the uniform location for a given attribute in the Light struct in the Fragment Shader.
void LightManager::setUniformAttrib(GLuint* uniformVar, char* attribName, GLuint program)
{
	for (int i = 0; i < 10; i++)
	{
		std::ostringstream ss;
		ss << "lights[" << i << "]." << attribName;
		uniformVar[i] = glGetUniformLocation(program, ss.str().c_str());
	}
}

void LightManager::setLights()
{
	glUniform1i(uniNumLights, numLights);
	for (int i = 0; i < numLights; i++)
	{
		glUniform4fv(uniLightPosition[i], 1, glm::value_ptr(lights[i].position));
		glUniform4fv(uniLightIntensity[i], 1, glm::value_ptr(lights[i].intensity));
	}
}

void LightManager::addLight(glm::vec3 pos, glm::vec3 intensity, LightType type)
{
	switch (type)
	{
	case POINT:
		lights[numLights].position = glm::vec4(pos, 1.0f);
		break;
	case DIRECTIONAL:
		lights[numLights].position = glm::vec4(pos, 0.0f);
		break;
	default:
		return;
		break;
	}

	lights[numLights].intensity = intensity;

	numLights++;
}