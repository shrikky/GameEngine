#version 440 core

#define MAX_LIGHTS 10

in vec2 TexCoords;
in vec3 normal;
in vec3 posOut;

out vec4 color;

struct Light
{
	vec4 position;
	vec3 intensity;
};

uniform sampler2D texture_diffuse1;
uniform int numLights;
uniform Light lights[MAX_LIGHTS];

vec4 diffuse()
{
	vec4 lightEffect = vec4(0.0f,0.0f,0.0f,0.0f);
	vec3 tempPosition;
	vec3 lightPath;
	float intensity;

	for (int i = 0; i < numLights; i++)
	{
		if (lights[i].position.w == 1)					// Point light
		{
			tempPosition = lights[i].position.xyz;
			lightPath = tempPosition - posOut;
		}
		else											// Directional Light
		{
			lightPath = lights[i].position.xyz;
		}

		intensity = max(dot(lightPath, normal), 0.0f);
		lightEffect += vec4(lights[i].intensity, 0.0f) * intensity;
	}

	lightEffect.w = 1.0f;

	return lightEffect;
}

void main()
{   

	color = vec4(texture(texture_diffuse1, TexCoords)) * diffuse();
}