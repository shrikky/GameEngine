#version 440

layout (location = 0) in vec4 VertexPosition;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * VertexPosition;
}