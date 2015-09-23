#version 330 core
out vec4 color;
void main()
{
	float ambientStrength = .75f;
    vec3 ambient = ambientStrength * vec3(1.0f,1.0f,1.0f);

    vec3 result = ambient * vec3(0.0f,0.0f,1.0f);
    color = vec4(result, 1.0f);
}