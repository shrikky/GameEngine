#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include "Transform.h"

class Collider3D
{
public:
	Collider3D();
	Collider3D(Transform* trans);
	~Collider3D();

	Transform* transform;
	std::vector<glm::vec3> edgeSet;
	std::vector<glm::vec3> vertexSet;
	std::vector<glm::vec3> faceNormalSet;

	void createBoxCollider(float length, float breadth, float width, int id);

	int id;
};


