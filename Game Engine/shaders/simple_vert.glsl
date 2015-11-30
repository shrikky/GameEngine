#version 440 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 posOut;
out vec3 normOut;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
	normOut = normalize(normal);
	posOut = (model * vec4(position,1.0f)).xyz;
    TexCoords = texCoords;
}