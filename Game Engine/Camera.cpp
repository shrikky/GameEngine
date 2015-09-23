#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::InitCamera(glm::vec3 pos, glm::vec3 forward, glm::vec3 up)
{
	campos = pos;
	camUp = up;
	camForward = forward;
}

glm::mat4 Camera::ReturnView(){
	glm::mat4 view;
	view = glm::lookAt(campos, campos+camForward, camUp);
	return view;
}

glm::mat4 Camera::ReturnPerspective(float fov, float aspratio, float near, float far){
	glm::mat4 _perspective = glm::perspective(fov, aspratio, near, far);
	return _perspective;

}