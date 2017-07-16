#version 330 core

in vec3 OutColor;
in vec4 OutColor2;
in vec2 TextCoord;

out vec4 FragColor;

uniform sampler2D TextureObject;		// the texture object will be passed here from the application program
										// just bind the texture object in the application and it will be autmatically assigned

void main()
{
	// sample and filter a color from the texture with this texture coordinates
	FragColor = texture(TextureObject, TextCoord) * OutColor;		


	// FragColor = outColor2;
	//FragColor = vec4(outColor, 1.0f);
	//"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}