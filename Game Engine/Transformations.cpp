#include "Transformations.h"


Transformations::Transformations()
{
}


Transformations::~Transformations()
{
}

void Transformations::TransformInit(glm::vec3 pos, glm::vec3 _scale, glm::vec3 rot){
	position = pos;
	scale = _scale;
	rotation = rot;
}

void Transformations::UpdatePosition(glm::vec3 pos){
	position += pos;
}

glm::mat4 Transformations::ReturnModelMatrix(){

	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
	rotation.x += 0.5f;
	model= glm::rotate(model, rotation.z, glm::vec3(0, 0, -1));
	model = glm::scale(model, scale);
	return model;
}
