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
	static ColliderManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new ColliderManager();
			return s_pInstance;
		}

		return s_pInstance;
	}
	void updateList();
	void create(float length, float breadth, float width, int id);

	std::vector<Collider3D *>  colliderUpdateList;
private:
	static ColliderManager* s_pInstance;
	ColliderManager();
	~ColliderManager();
	float overlap(float min1, float max1, float min2, float max2);
	glm::vec3 getMinMax(glm::vec3 n, Collider3D A, float &min, float &max);
	glm::vec3 getPOCin1D(Collider3D A, Collider3D B, glm::vec3 n);
	glm::vec3 LineCollision(Line &l1, Line &l2);

	bool isColliding(Collider3D A, Collider3D B, glm::vec3 &mtv);
	glm::vec3 getpointOfCollision(Collider3D &A, Collider3D &B, glm::vec3 mtv);
};