#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	
	float shininess;
};

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 color;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TextCoords;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

out vec4 FragColor;

void main()
{	
	// Vectors
	vec3 normVec  = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir  = normalize(viewPos - FragPos);
	
	// Ambient
	//float ambientStrength = 0.5f;
	vec3 ambientColor = texture(material.diffuse, TextCoords).rgb * light.ambient;

	// Diffuse
	float diff = max(dot(normVec, lightDir), 0.0f);
	vec3 diffColor = diff * texture(material.diffuse, TextCoords).rgb  * light.diffuse; 

	// Specular
	vec3 reflectedDir = reflect(-lightDir, normVec);
	float spec = pow(max(dot(reflectedDir, viewDir), 0.0f), material.shininess);
	//float specularStrength = 0.5f;
	vec3 specularColor = spec * texture(material.specular, TextCoords).rgb * light.specular;

	// Final Color
	vec3 resultColor = (specularColor + diffColor + ambientColor) ; //* objectColor;
	FragColor = vec4(resultColor, 1.0f);
}