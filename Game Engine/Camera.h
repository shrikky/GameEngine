#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
	glm::vec3 campos;
	glm::vec3 camUp;
	glm::vec3 camForward;

public:
	Camera(); 
	~Camera();
	void InitCamera(glm::vec3 pos, glm::vec3 forward, glm::vec3 up);
	glm::mat4 ReturnPerspective(float fov, float aspratio, float near, float far);
	glm::mat4 ReturnView();
};

