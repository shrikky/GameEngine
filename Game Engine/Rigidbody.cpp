#include "Rigidbody.h"


Rigidbody::Rigidbody()
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Rigidbody_Init(int id) {
	current.id = 0;
	current.transform = TransformManager::Instance()->transformList[0];
	current.size = 1;
	current.mass = 1;
	current.inverseMass = 1.0f / current.mass;
	current.momentum = glm::vec3(0, 0, 0);
	current.angularMomentum = glm::vec3(0, 0, 0);
	current.inertiaTensor = current.mass * current.size * current.size * 1.0f / 6.0f;
	current.inverseInertiaTensor = 1.0f / current.inertiaTensor;
	current.recalculate();
	previous = current;
}
