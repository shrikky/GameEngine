#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::create()
{
	this->position = glm::vec3(0.0f);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
	this->modelMatrix = glm::mat4(1.0f);
}