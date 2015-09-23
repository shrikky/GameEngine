#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Transformations
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	
public:
	Transformations();
	~Transformations();
	void TransformInit(glm::vec3 pos, glm::vec3 _scale, glm::vec3 rot);
	void UpdatePosition(glm::vec3 pos);
	glm::mat4 ReturnModelMatrix();
};

