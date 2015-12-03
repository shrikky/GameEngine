#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include "Collider3D.h"

struct Line{
	glm::vec3 point1;
	glm::vec3 point2;
};

class ColliderManager
{
public:
	ColliderManager();
	~ColliderManager();
	void updateList();
	
	std::vector<Collider3D *>  colliderUpdateList;
private:
	float overlap(float min1, float max1, float min2, float max2);
	glm::vec3 getMinMax(glm::vec3 n, Collider3D A, float &min, float &max);
	glm::vec3 getPOCin1D(Collider3D A, Collider3D B, glm::vec3 n);
	glm::vec3 LineCollision(Line &l1, Line &l2);
	
	bool isColliding(Collider3D A, Collider3D B, glm::vec3 &mtv);
	glm::vec3 getpointOfCollision(Collider3D &A, Collider3D &B, glm::vec3 mtv);
};