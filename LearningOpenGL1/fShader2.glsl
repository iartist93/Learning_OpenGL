#version 330 core

in vec3 Normal;
in vec3 FragPos;


uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;

out vec4 FragColor;


void main()
{
	// Ambient
	float ambientStrength = 0.5f;
	vec3 ambientColor = ambientStrength * lightColor;

	// Diffuse
	vec3 normVec = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffFact = max(dot(normVec, lightDir), 0.0f);
	vec3 diffColor = diffFact * lightColor; 

	// Final Color
	vec3 resultColor = (diffColor + ambientColor) * objectColor;
	FragColor = vec4(resultColor, 1.0f);
}