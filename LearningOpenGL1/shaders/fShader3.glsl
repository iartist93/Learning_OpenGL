#version 330 core

uniform vec3 lightColorNow;

out vec4 FragColor;

void main()
{
	//FragColor = vec4(1.0f);
	FragColor = vec4(lightColorNow, 1.0f);
}