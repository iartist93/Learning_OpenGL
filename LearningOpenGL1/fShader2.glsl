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

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;	
};

struct PointLight
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float range;
	float constant;
	float linear;
	float quadratic;
};

struct FlashLight
{
	vec3 position;
	vec3 direction;

	float innerCutoff;		// inner coine cutoff = Phi
	float outterCutoff;		// outt coine cuttoff = gamma

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

//-------------- inputs -------------------//

in vec3 Normal;
in vec3 FragPos;
in vec2 TextCoords;

uniform vec3 viewPos;
uniform Material material;

//----------- light uniforms --------------//

uniform int numPointLight;
uniform int numDirLight;
uniform int numFlashLight;

uniform DirLight   dirLights[1];
uniform PointLight pointLights[1];
uniform FlashLight flashLights[1];

//-------------- outputs -------------------//

out vec4 FragColor;

//---------- Directional Light  ------------//

// Calc the impact of specific light on the current fragement

vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir)		// things that're passed from the main()
{
	vec3 ambientColor = texture(material.diffuse, TextCoords).rgb * light.ambient;

	float diff = max(dot(normalize(-light.direction), normal), 0.0f);
	vec3 diffColor = texture(material.diffuse, TextCoords).rgb * light.diffuse;

	vec3 reflectedDir = reflect(light.direction, normal);		// direcion from the light to the frag
	float spec = pow(max(dot(viewDir, reflectedDir), 0.0f), material.shininess);
	vec3 specularColor = texture(material.specular, TextCoords).rgb * light.specular * spec;

	return (ambientColor + diffColor + specularColor);
}

//--------------- Point Light  -------------//

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	// we care about the position of the point light to calculate the attenuation
	// we care about the direction between the fragement position and the light to get calculate the specularity

	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + (light.linear * distance) + (light.quadratic * distance * distance));

	vec3 lightDir = normalize(light.position - fragPos);
	
	vec3 ambientColor = texture(material.diffuse, TextCoords).rgb * light.ambient * attenuation;

	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuseColor = texture(material.diffuse, TextCoords).rgb * diff * light.diffuse * attenuation;

	vec3 reflectedDir = reflect(-lightDir, normal);	// both are normalized already
	float spec = pow(max(dot(viewDir, reflectedDir), 0.0f), material.shininess);
	vec3 specularColor = texture(material.specular, TextCoords).rgb * spec * light.specular * attenuation;

	return (ambientColor + diffuseColor + specularColor);
}


//--------------- Flash Light  -------------//

vec3 CalculateFlashLight(FlashLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	// spotlight soft-edge
	float theta = dot(-lightDir, normalize(light.direction));
	float epsilon = light.innerCutoff - light.outterCutoff; // inner - outter
	float intensity = clamp((theta - light.outterCutoff) / epsilon, 0.0, 1.0);
	
	vec3 resultColor;

	if(theta > light.outterCutoff)	// frag inside
	{
		float distance = length(light.position - FragPos);
		float attenuation = light.constant + (light.linear * distance) + (light.quadratic * distance * distance);
		float luminosity = 1.0f / attenuation;

		vec3 ambientColor = texture(material.diffuse, TextCoords).rgb * light.ambient;

		float diff = max(dot(lightDir, normal), 0.0f);
		vec3 diffuseColor = diff * texture(material.diffuse, TextCoords).rgb  * light.diffuse * luminosity;

		vec3 reflectedDir = reflect(-lightDir, normal);
		float spec = pow(max(dot(reflectedDir, viewDir), 0.0f), material.shininess);
		vec3 specularColor = spec * texture(material.specular, TextCoords).rgb * light.specular * luminosity;

		resultColor = (ambientColor + diffuseColor + specularColor) ; //* objectColor;	
	} 
	else 	// use only the ambient light
	{
		resultColor = light.ambient * vec3(texture(material.diffuse, TextCoords));
	}

	return resultColor;
}

//-------------------------------------------------------------//

void main()
{
	vec3 normal  = normalize(Normal);	
	vec3 viewDir  = normalize(viewPos - FragPos);

	vec3 outputColor = vec3(0.0f);

	for(int i = 0; i < 1; i++)
	{
		outputColor += CalculatePointLight(pointLights[i], normal, FragPos, viewDir);
	}

	for(int i = 0; i < 1; i++)
	{
		outputColor += CalculateDirLight(dirLights[i], normal, viewDir);
	}

	for(int i = 0; i < 1; i++)
	{
		outputColor += CalculateFlashLight(flashLights[i], normal, FragPos, viewDir);
	}

	FragColor = vec4(outputColor, 1.0f);
}