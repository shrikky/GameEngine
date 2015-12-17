#include "ColliderManager.h"

ColliderManager* ColliderManager::s_pInstance = 0;

ColliderManager::ColliderManager()
{
}


ColliderManager::~ColliderManager()
{
}

//Function to check if the two ranges from min1 to max1, and min2 to max2 overlap.
float ColliderManager::overlap(float min1, float max1, float min2, float max2)
{
	// Case 2 : min1 lies on the left of min2
	if (min1 < min2)
	{
		if (max1 >= max2)
			return max2 - min2;			// overlap, return positive

		return max1 - min2;				// If overlap, then return positive else negative
	}

	// Case 3 : min1 lie between min2 and max2
	if (min1 >= min2 && min1 < max2)
	{
		if (max1 <= max2)				// segment1 lies completly inside 2
			return max1 - min1;

		return max2 - min1;
	}

	//Case 1 : min1 lies outside max2
	if (min1 >= max2)
		return max2 - min1;				// no overlap, return negative

}



// This function gets the minimum and maximul values of an object projected on the vector n. It also returns the vertex which is projecting the lowest value.
// This is a redundant operation in this example. Thus, it makes sense in encapsulating it in a function.
glm::vec3 ColliderManager::getMinMax(glm::vec3 n, Collider3D A, float &min, float &max)
{
	n = glm::normalize(n);
	float temp;
	min = 99.0f;				// Set min to the maximum possible value.
	max = -99.0f;				// Set max to minimum possible value.
	std::vector<glm::vec3>::iterator xy;
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), A.transform->position) * glm::mat4_cast(A.transform->rotation);
	glm::vec3 minvector(0.0f, 0.0f, 0.0f);

	for (xy = A.vertexSet.begin(); xy != A.vertexSet.end(); xy++)
	{
		temp = glm::dot(n, glm::vec3(transform * glm::vec4(*xy, 1.0f)));
		if (min > temp)					// If the current min is greater than the temp value, then replace min with the temp value.
		{
			min = temp;
			minvector = glm::vec3(transform * glm::vec4(*xy, 1.0f));
		}
		if (max < temp)					//If the current max is less than the temp value, then replace max with the temp value.
			max = temp;
	}

	return minvector;					// return the point projecting the minimum value.
}


glm::vec3 ColliderManager::getPOCin1D(Collider3D A, Collider3D B, glm::vec3 n)
{
	n = glm::normalize(n);				
	float min1, min2, max1, max2, o;
	glm::vec3 POC;

	getMinMax(n, A, min1, max1);		
	getMinMax(n, B, min2, max2);		

	o = overlap(min1, max1, min2, max2);

	if (min1 < min2)					
	{									
		POC = n * (min2 + (o / 2.0f));	
	}
	else
		POC = n * (min1 + (o / 2.0f));

	return POC;
}


glm::vec3 ColliderManager::LineCollision(Line &l1, Line &l2)
{
	glm::vec3 d1, d2, r;
	d1 = l1.point2 - l1.point1;
	d2 = l2.point2 - l2.point1;
	r = l1.point1 - l2.point1;

	float a = glm::dot(d1, d1);
	float b = glm::dot(d1, d2);
	float c = glm::dot(d1, r);
	float e = glm::dot(d2, d2);
	float f = glm::dot(d2, r);

	float d = (a*e) - (b*b);

	float s = ((b*f) - (c*e)) / d;
	float t = ((a*f) - (b*c)) / d;

	glm::vec3 p1, p2;
	p1 = l1.point1 + (s * d1);
	p2 = l2.point1 + (t * d2);

	return (p1 + p2) / 2.0f;
}

bool ColliderManager::isColliding(Collider3D A, Collider3D B, glm::vec3 &mtv)
{
	glm::vec3 n;
	//set the min and max values to highest possible values.
	float min1 = 99.0f, max1 = -99.0f, min2 = 99.0f, max2 = -99.0f, temp;
	// Vector to maintain the overlaps along each axis. If there is no overlap, then the distance stored here would be negative
	std::vector<float> overlaps;
	// Vector to store the axes. This is used to lookup thich axis had the smallest overlap. This data structure is in sync with the overlaps vector
	std::vector<glm::vec3> MTV;

	// the transform matrices for each object
	glm::mat4 transform1, transform2;

	//transform matrices consist of translation and rotation matrix of each respective object
	transform1 = A.transform->returnModelMatrix();
	transform2 = B.transform->returnModelMatrix();

	std::vector<glm::vec3>::iterator it, xy;

	// Go through face normals of box1
	for (it = A.faceNormalSet.begin(); it != A.faceNormalSet.end(); it++)
	{
		n = glm::normalize(*it);
		n = glm::vec3(transform1 * glm::vec4(n, 0.0f));
		n = glm::normalize(n);
		MTV.push_back(n);											// store the data for later use

		min1 = 99.0f;
		max1 = -99.0f;
		min2 = 99.0f;
		max2 = -99.0f;

		//find the dot produnct of each vertex in world space on the axis
		getMinMax(n, A, min1, max1);

		//find the dot produnct of each vertex in world space on the axis
		getMinMax(n, B, min2, max2);

		if (min1 >= max2 || max1 <= min2)
			return false;							// If overlap occours in any of the axis, then the objects are not intersecting : early exit

		overlaps.push_back(overlap(min1, max1, min2, max2));		// store the data for later use
	}

	//For face normals of box2
	for (it = B.faceNormalSet.begin(); it != B.faceNormalSet.end(); it++)
	{
		n = glm::normalize(*it);
		n = glm::vec3(transform2 * glm::vec4(n, 0.0f));
		n = glm::normalize(n);
		MTV.push_back(n);													// store the data for later use

		min1 = 99.0f;
		max1 = -99.0f;
		min2 = 99.0f;
		max2 = -99.0f;

		//find the dot produnct of each vertex in world space on the axis
		getMinMax(n, A, min1, max1);

		//find the dot produnct of each vertex in world space on the axis
		getMinMax(n, B, min2, max2);

		if (min1 >= max2 || max1 <= min2)
			return false;													// If overlap occours in any of the axis, then the objects are not intersecting : early exit

		overlaps.push_back(overlap(min1, max1, min2, max2));				// store the data for later use
	}

	std::vector<glm::vec3>::iterator ab;

	//For edges of (box1 X box2)
	for (it = A.edgeSet.begin(); it != A.edgeSet.end(); it++)
	{
		for (ab = B.edgeSet.begin(); ab != B.edgeSet.end(); ab++)
		{
			n = glm::normalize(*it);
			n = glm::vec3(transform1 * glm::vec4(n, 0.0f));
			n = glm::cross(n, glm::vec3(transform2 * glm::vec4(*ab, 0.0f)));

			if (glm::length(n) > FLT_EPSILON)
			{
				n = glm::normalize(n);
				MTV.push_back(n);														// store the data for later use

				min1 = 99.0f;
				max1 = -99.0f;
				min2 = 99.0f;
				max2 = -99.0f;
				//find the dot produnct of each vertex in world space on the axis
				getMinMax(n, A, min1, max1);

				//find the dot produnct of each vertex in world space on the axis
				getMinMax(n, B, min2, max2);

				if (min1 >= max2 || max1 <= min2)
					return false;														// If overlap occours in any of the axis, then the objects are not intersecting : early exit

				overlaps.push_back(overlap(min1, max1, min2, max2));					// store the data for later use
			}
		}
	}

	float min = 9999999;
	n = glm::vec3(0.0f, 0.0f, 0.0f);

	// At this point we are sure that the objects are intersecting. 
	// No we have to find the smallest overlap, and the corresponding axis.
	for (int i = 0; i < overlaps.size(); i++)
	{
		if (min > overlaps[i] && overlaps[i] > 0.0f)
		{
			min = overlaps[i];
			n = MTV[i];
		}
	}

	// making sure that the axis points from A to B
	glm::vec3 d = B.transform->position - A.transform->position;


	if (glm::dot(d, n) < 0.0f)
		n *= -1.0f;

	// multiplying the overlap with the unit vector gives the MTV
	mtv = n * min;

	//return true for collision detection
	return true;

}

glm::vec3 ColliderManager::getpointOfCollision(Collider3D &A, Collider3D &B, glm::vec3 mtv)
{
	glm::vec3 n = glm::normalize(mtv);

	float tolerance = 0.01f;

	int totalSuspects1 = 1, totalSuspects2 = 1;

	// the transform matrices for each object
	glm::mat4 transform1, transform2;
	glm::vec3 pointofCollision;

	glm::vec3 closestPointsA[2], ClosestPointsB[2];

	//transform matrices consist of translation and rotation matrix of each respective object
	transform1 = A.transform->returnModelMatrix() ;
	transform2 = B.transform->returnModelMatrix() ;

	float pointsA, pointsB;
	std::vector<glm::vec3>::iterator it;

	//Set the min to maximum possible value, and max to minimum possible value
	float max = -99.0f, min = 99.0f;
	int i;

	for (it = A.vertexSet.begin(); it != A.vertexSet.end(); it++)
	{
		pointsA = (glm::dot(glm::vec3(transform1*(glm::vec4(*it, 1.0f))), n));

		if (abs(max - pointsA) <= tolerance)
		{
			closestPointsA[1] = *it;			// If any other point lies close to the given point within the tolerance level, increment the total number of suspects. 
			totalSuspects1++;					// update the closest poitns set
		}
		else
			if (max < pointsA)						// If another point is found which is closer then reset the count and store the 2 closest points 
			{
				max = pointsA;
				totalSuspects1 = 1;
				pointofCollision = *it;
				closestPointsA[0] = pointofCollision;
				closestPointsA[1] = pointofCollision;
			}
	}

	//Point to face or edge collision, with point of object A piercing object B
	if (totalSuspects1 == 1)
	{
		return glm::vec3(transform1*(glm::vec4(pointofCollision, 1.0f)));
	}

	for (it = B.vertexSet.begin(); it != B.vertexSet.end(); it++)
	{
		pointsB = (glm::dot(glm::vec3(transform2*(glm::vec4(*it, 1.0f))), n));

		if (abs(min - pointsB) <= tolerance)
		{
			ClosestPointsB[1] = *it;							// If any other point lies close to the given point within the tolerance level, increment the total number of suspects. 
			totalSuspects2++;									// update the closest poitns set
		}
		else
			if (min > pointsB)
			{
				min = pointsB;
				totalSuspects2 = 1;									// If another point is found which is closer then reset the count and store the 2 closest points 
				pointofCollision = *it;
				ClosestPointsB[0] = pointofCollision;
				ClosestPointsB[1] = pointofCollision;
			}
	}

	//Point to face or edge collision, with point of object B piercing object A
	if (totalSuspects2 == 1)
	{
		return glm::vec3(transform2*(glm::vec4(pointofCollision, 1.0f)));
	}

	//If the number of suspects is exactly 2 on both sides, then the collision is edge to edge
	//Edge to edge collision
	if (totalSuspects1 == 2 && totalSuspects2 == 2)
	{
		Line l1, l2;																		// Create two lines with the values we stored earlier in the previous steps. 
		l1.point1 = glm::vec3(transform1 * glm::vec4(closestPointsA[0], 1.0f));
		l1.point2 = glm::vec3(transform1 * glm::vec4(closestPointsA[1], 1.0f));

		l2.point1 = glm::vec3(transform2 * glm::vec4(ClosestPointsB[0], 1.0f));
		l2.point2 = glm::vec3(transform2 * glm::vec4(ClosestPointsB[1], 1.0f));

		return LineCollision(l1, l2);														// Pass them to deduce the point of collision
	}

	//If we have reached this point, then the face of one of the objects is colliding with the edge or the face of
	//the other object, as the suspects count has to be greater than 2 for both the objects.
	// edge-face collision or face face collision;

	//here v1,v2 and v3 are the basis vector we will derive from n, using grahm-schmidt's process
	//v1 = x-axis
	//v2 = y-axis
	//v3 = z-axis
	glm::vec3 v1, v2, v3;
	v1 = glm::vec3(1.0f, 0.0f, 0.0f) - n * n.x;									// Subtract the component of the vector n on X-axis to get the first basis vector. 									
	v2 = glm::vec3(0.0f, 1.0f, 0.0f) - n*n.y - v1 * v1.y;						// Subtract the component of the vector n on Y axis and v1 on Yaxis to get the second vector
	v3 = glm::vec3(0.0f, 0.0f, 1.0f) - n*n.z - (v1* v1.z) - (v2* v2.z);			// subtract the component of the vector n on Z axis and v1 on Z axis and v2 on Zaxis to get the third basis vector

	//We only need 2 basis vectors, So we choose 2 of those which are not 0.
	// Since we are dealing with a small system here, FLT_EPSILON is not enough of a error margin, so we multiply it by 2 to increase it.

	//This section of code basically, swaps the three vectors v1,v2,and v3 such that the non-zero vectors are always stored in v1 and v2
	if (glm::length(v1) < 2.0f*FLT_EPSILON)
	{
		if (glm::length(v3) > 2.0f*FLT_EPSILON)
			v1 = v3;
	}
	else if (glm::length(v2) < 2.0f * FLT_EPSILON)
	{
		if (glm::length(v3) > 2.0f * FLT_EPSILON)
			v2 = v3;
	}

	v1 = glm::normalize(v1);
	v2 = glm::normalize(v2);

	glm::vec3 component1, component2, component3, POC;

	//get the component along the two vectors and add it.
	component1 = getPOCin1D(A, B, v1);
	component2 = getPOCin1D(A, B, v2);

	POC = component1 + component2;

	//adding the resultant with the distance of the plane from the origin multiplied by the normal(plane) will give us the position of the point.
	float d = glm::dot(n, (glm::vec3(transform2*(glm::vec4(ClosestPointsB[0], 1.0f)))));

	return POC + d * n;

}

void ColliderManager::create(float length, float breadth, float width, int id)
{
	Collider3D* collider = new Collider3D;
	collider->createBoxCollider(length, breadth, width, id);

	colliderUpdateList.push_back(collider);
}

void ColliderManager::updateList()
{
	glm::vec3 mtv;
	if (colliderUpdateList.size() > 1)
	for (int i = 1; i < colliderUpdateList.size(); i++)
	{
		if (isColliding(*(colliderUpdateList[i]), *(colliderUpdateList[i-1]), mtv))
		{
			// MTV contains the mininum translation vector
			// Use getPointOfCollision to get the point of contact and use it to resolve collision
			std::cout << "Objects are colliding";
			std::cout << "ids: " << colliderUpdateList[i]->id << " " << colliderUpdateList[i - 1]->id;
		}
	}
}