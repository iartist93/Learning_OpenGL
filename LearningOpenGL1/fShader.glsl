#version 330 core

in vec3 OutColor;
in vec4 OutColor2;
in vec2 TextCoord;

out vec4 FragColor;

uniform sampler2D TextureObject1;
uniform sampler2D TextureObject2;
										

void main()
{
	// sample and filter a color from the texture with this texture coordinates
	FragColor = mix(texture(TextureObject1, TextCoord), texture(TextureObject2, TextCoord), 0.4);	// 80% First 20% second 

	// FragColor = texture(TextureObject2, TextCoord) ;//* OutColor ;		
	// FragColor = outColor2;
	//FragColor = vec4(outColor, 1.0f);
	//"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}