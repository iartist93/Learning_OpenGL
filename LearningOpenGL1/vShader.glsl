#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 OutColor;
out vec4 OutColor2;
out vec2 TextCoord;

uniform mat4 transform;				// <-- pass the final transform matrix from the app to here


void main()
{

	gl_Position = transform * vec4(aPos, 1.0f);		
	// gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	
	OutColor  = aColor;
	OutColor2 = gl_Position;
	TextCoord = vec2(aTexCoord.x, 1 - aTexCoord.y);
}