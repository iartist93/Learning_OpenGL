#version 330 core

in vec3 Normal;
in vec3 FragPos;


uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;


void main()
{	
	// Vectors
	vec3 normVec  = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir  = normalize(viewPos - FragPos);
	
	// Ambient
	float ambientStrength = 0.5f;
	vec3 ambientColor = ambientStrength * lightColor;

	// Diffuse
	float diffFact = max(dot(normVec, lightDir), 0.0f);
	vec3 diffColor = diffFact * lightColor; 

	// Specular
	vec3 reflectedDir = reflect(-lightDir, normVec);
	float spec = pow(max(dot(reflectedDir, viewDir), 0.0f), 32);
	float shininess = 0.5f;
	vec3 specularColor = spec * shininess * lightColor;

	// Final Color
	vec3 resultColor = (specularColor + diffColor + ambientColor) * objectColor;
	FragColor = vec4(resultColor, 1.0f);
}