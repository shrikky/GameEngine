#version 440

layout (location = 0) in vec4 VertexPosition;

out vec4 outPos;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	outPos = projection * view * VertexPosition;
    gl_Position = outPos; 
}