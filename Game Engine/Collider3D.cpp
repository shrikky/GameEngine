#include "Collider3D.h"


Collider3D::Collider3D()
{
}

Collider3D::Collider3D(Transform* trans)
{
	transform = trans;
}

Collider3D::~Collider3D()
{
}

void Collider3D::createBoxCollider(float length, float breadth, float width)
{
/*
	a-----------b
	|   FRONT	|	length
	c-----------d
	   breadth
	x-----------y
	|	BACK	|
	z-----------w
*/
	glm::vec3 a, b, c, d;
	glm::vec3 x, y, z, w;

	a = glm::vec3(-breadth / 2.0f, length / 2.0f, width / 2.0f);
	b = glm::vec3(breadth / 2.0f, length / 2.0f, width / 2.0f);
	c = glm::vec3(-breadth / 2.0f, -length / 2.0f, width / 2.0f);
	d = glm::vec3(breadth / 2.0f, -length / 2.0f, width / 2.0f);

	x = glm::vec3(-breadth / 2.0f, length / 2.0f, -width / 2.0f);
	y = glm::vec3(breadth / 2.0f, length / 2.0f,  -width / 2.0f);
	z = glm::vec3(-breadth / 2.0f, -length / 2.0f,-width / 2.0f);
	w = glm::vec3(breadth / 2.0f, -length / 2.0f, -width / 2.0f);

	vertexSet.push_back(a);
	vertexSet.push_back(b);
	vertexSet.push_back(c);
	vertexSet.push_back(d);
	vertexSet.push_back(x);
	vertexSet.push_back(y);
	vertexSet.push_back(z);
	vertexSet.push_back(w);

	edgeSet.push_back(a - b);
	edgeSet.push_back(c - a);
	edgeSet.push_back(d - c);
	edgeSet.push_back(b - d);

	edgeSet.push_back(x - y);
	edgeSet.push_back(z - x);
	edgeSet.push_back(w - z);
	edgeSet.push_back(y - w);

	faceNormalSet.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	faceNormalSet.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	faceNormalSet.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
}