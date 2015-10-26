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

void Transform::update()
{
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, scale);

	position = glm::vec3(0);
}

void Transform::translate(glm::vec3& pos)
{
	this->position += pos;
}