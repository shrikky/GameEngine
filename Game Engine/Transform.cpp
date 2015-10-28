#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::create(int id)
{
	this->id = id;
	this->position = glm::vec3(0.0f);
	this->rotation.x = this->rotation.y = this->rotation.z = 0.0f;
	this->rotation.w = 1.0f;
	this->scale = glm::vec3(1.0f);
	this->modelMatrix = glm::mat4(1.0f);
}

void Transform::update()
{
	modelMatrix = glm::translate(modelMatrix, position);
	glm::mat4 rotMatrix = glm::mat4_cast(rotation);
	modelMatrix = modelMatrix * rotMatrix;
	modelMatrix = glm::scale(modelMatrix, scale);
	position = glm::vec3(0);
}

void Transform::translate(glm::vec3& pos)
{
	this->position += pos;
}

void Transform::render(Shader* shaderList) {
	glUniformMatrix4fv(glGetUniformLocation(shaderList->Program, "model"), 1, GL_FALSE, glm::value_ptr(this->returnModelMatrix()));
}