#include "Rigidbody.h"


Rigidbody::Rigidbody()
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Rigidbody_Init() {
	current.size = 1;
	current.mass = 1;
	current.inverseMass = 1.0f / current.mass;
	current.position = glm::vec3(2, 0, 0);
	current.momentum = glm::vec3(0, 0, -10);
	current.orientation.x = current.orientation.y = current.orientation.z = 0;
	current.orientation.w = 1;
	current.angularMomentum = glm::vec3(0, 0, 0);
	current.inertiaTensor = current.mass * current.size * current.size * 1.0f / 6.0f;
	current.inverseInertiaTensor = 1.0f / current.inertiaTensor;
	current.recalculate();
	previous = current;
}
