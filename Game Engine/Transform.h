#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{	
public:
	Transform();
	~Transform();

	void create();
	void update();

	void translate(glm::vec3& pos);
	glm::mat4 returnModelMatrix() { return modelMatrix; }

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 modelMatrix;
};

