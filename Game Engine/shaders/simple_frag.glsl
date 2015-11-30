#version 440 core

#define MAX_LIGHTS 10

in vec2 TexCoords;
in vec3 normOut;
in vec3 posOut;

out vec4 color;

struct Light
{
	vec4 position;
	vec4 intensity;
	//float padding;
};

uniform sampler2D texture_diffuse1;
uniform int numLights;
uniform Light lights[MAX_LIGHTS];

vec4 diffuse(vec4 ambientColor)
{
	vec4 lightEffect = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vec3 lightPath;
	float intensity;

	for (int i = 0; i < numLights; i++)
	{
		if (lights[i].position.w == 1)					// Point light
		{
			lightPath = normalize(lights[i].position.xyz - posOut);
		}
		else											// Directional Light
		{
			lightPath = normalize(-lights[i].position.xyz);
		}

		intensity = max(dot(lightPath, normOut), 0.0f);
		lightEffect += vec4((lights[i].intensity.xyz * ambientColor.xyz) * (intensity), 0.0f);
	}

	lightEffect.w = 1.0f;
	return lightEffect;
}

void main()
{   
	vec4 AmbientColor = vec4(texture(texture_diffuse1, TexCoords)) * 0.4f;
	color = diffuse(AmbientColor);
	//color = vec4(lights[0].intensity, 1.0f);
}