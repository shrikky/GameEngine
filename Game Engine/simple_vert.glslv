#version 330 core
layout (location = 0) in vec3 i_position;
uniform mat4 perspectiveMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
void main()
{
	mat4 mvp = perspectiveMatrix*viewMatrix*modelMatrix;

	gl_Position = mvp*vec4(i_position.x, i_position.y, i_position.z, 1.0);
}
