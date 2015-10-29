#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLM/gtc/quaternion.hpp>
#include "Shader.h"

class Transform
{	
public:
	int id;
	Transform();
	~Transform();

	void create(int id);
	void update();
	void render(Shader*);
	void translate(glm::vec3& pos);
	void resetRotation();
	glm::mat4 returnModelMatrix() { return modelMatrix; }
	
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
	glm::mat4 modelMatrix;
private:

};

